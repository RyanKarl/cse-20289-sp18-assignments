/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s files...\n", progname);
    exit(status);
}

/**
 * Save list of file paths to temporary file.
 * @param   files       Array of path strings.
 * @param   n           Number of path strings.
 * @return  Newly allocated path to temporary file.
 */
char *	save_files(char **files, size_t n) {
    char * path = strdup("moveit-XXXXXX");
    int fd = mkstemp(path);
    FILE * file = fdopen(fd, "w+");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", strerror(errno));
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        fprintf(file, "%s\n", files[i]);
    }

    fclose(file);

    return path;
}

/**
 * Run $EDITOR on specified path.
 * @param   path        Path to file to edit.
 * @return  Whether or not the $EDITOR process terminated successfully.
 */
bool	edit_files(const char *path) {
    char * editor = getenv("EDITOR");
    char * vim = "vim";
    if (editor == NULL || streq(editor, "false")) editor = vim;
    int status;
    pid_t pid  = fork();
    switch(pid)
    {
        case -1:
            fprintf(stderr, "Unable to fork %s\n", strerror(errno));
            return false;
            break;
        case 0:
            execlp(editor, editor, path, NULL);
            fprintf(stderr, "exec %s has failed: %s\n", editor, strerror(errno));
            return false;
            break;
        default:
            if (wait(&status) < 0){
                fprintf(stderr, "wait has failed: %s\n", strerror(errno));
                return false;
            }
            break;
    }

    return true;
}

/**
 * Rename files as specified in contents of path.
 * @param   files       Array of old path names.
 * @param   n           Number of old path names.
 * @param   path        Path to file with new names.
 * @return  Whether or not all rename operations were successful.
 */
bool	move_files(char **files, size_t n, const char *path) {
    
    FILE* f = fopen(path, "r");
    if (f == NULL)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        char buffer[BUFSIZ];
        char *fg = fgets(buffer, BUFSIZ, f);
        if (fg == NULL)
        {
            fclose(f);
            return true;
        }

        strchomp(buffer);

        if (!streq(files[i], buffer))
        {
            int r = rename(files[i], buffer);
            if (r == -1)
            {
                fclose(f);
                return false;
            }
        }
    }

    fclose(f);
    return true;
}

/* Main Execution */

int	main(int argc, char *argv[]) {

    if (argc == 1)
    {
        usage(argv[0], 1);
        return EXIT_FAILURE;
    }
    
    if (streq(argv[1], "-h"))
    {
        usage(argv[0], 0);
        return EXIT_SUCCESS;
    }

    char ** files = malloc((argc - 1)*sizeof(char*));
    for (int i = 1; i < argc; i++)
    {
        files[i - 1] = argv[i];

    }

    int n = argc -1;
    char * path = save_files(files, n);
    if(edit_files(path))
    {
        if (!move_files(files, n, path)){
            free(files);
            unlink(path);
            free(path);
            return EXIT_FAILURE;
        }
    }
   
    else
    {
        free(files);
        unlink(path);
        free(path);
        exit(EXIT_FAILURE);
    }

    free(files);
    unlink(path);
    free(path);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
