/* moveit.c: Interactive Move Command */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

/* Macros */

#define	streq(a, b) (strcmp(a, b) == 0)
#define strchomp(s) (s)[strlen(s) - 1] = 0
#define debug(M, ...) \
    if (Verbose) { \
        fprintf(stderr, "%s:%d:%s: " M, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    }

#define BILLION 1000000000L;

/* Globals */

int  Timeout = 10;
bool Verbose = false;

/* Functions */

/**
 * Display usage message and exit.
 * @param   progname    Program name.
 * @param   status      Exit status.
 */
void	usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] command...\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    -t SECONDS  Timeout duration before killing command (default is %d)\n", Timeout);
    fprintf(stderr, "    -v          Display verbose debugging output\n");
    exit(status);
}

/**
 * Parse command line options.
 * @param   argc        Number of command line arguments.
 * @param   argv        Array of command line argument strings.
 * @return  Array of strings representing command to execute.
 */
char ** parse_options(int argc, char **argv) {

    if(argc == 1)
    {
        usage (argv[0], 1);
        return NULL;
    }

    int argind = 1;
    while (argind < argc && strlen(argv[argind]) > 0 && argv[argind][0] == '-')
    {
        if (streq(argv[argind], "-t"))
        {
            argind++;
            Timeout = atoi(argv[argind]);
        }
        else if (streq(argv[argind], "-v"))
        {
            Verbose = true;
        }
        else if (streq(argv[argind], "-h"))
        {
            usage(argv[0], 0);
            return NULL;
        }
     
        argind++;
    }

    debug("Timeout = %d\n", Timeout);
    debug("Verbose = %d\n", Verbose);

    int i = 0;
    char ** command = NULL; 
    if (argind < argc-1) 
    {
        command = calloc((argc - argind+1), sizeof(char *));
    }
    else
    {
        usage(argv[0], 1);
        return NULL;
    }
    
    debug("Command = ");
    while (argind < argc)
    {
        printf("%s ", argv[argind]);
        command[i] = argv[argind];
        argind++;
        i++;
    }

    printf("\n");
    command[i] = (char *) NULL;
    if (command[0] == NULL)
    {
        return NULL;
    }

    return command;
}

/**
 * Handle signal.
 * @param   signum      Signal number.
 */
void    handle_signal(int signum) {
    debug("Received interrupt: %d\n", signum);
}

/* Main Execution */

int	main(int argc, char *argv[]) {
    
    signal(SIGCHLD, handle_signal);   // Register handler

    char ** command = parse_options(argc, argv);
    if (command == NULL)
    {
        return EXIT_FAILURE;
    }

    debug("%s\n", "Registering handlers...");
    signal(SIGCHLD, handle_signal);

    struct timespec start, end, t1;
    start.tv_sec = Timeout;
    start.tv_nsec = 0;
    debug("%s\n", "Grabbing start time...");
    int t = clock_gettime(CLOCK_MONOTONIC, &start);
    if (t < 0)
    {
        fprintf(stderr, "GetTime Failed: %s\n", strerror(errno));
        free(command);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    int status, w;

    switch(pid)
    {
        case -1:
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
            free(command);
            return EXIT_FAILURE;
            break;
        case 0:
            debug("Executing child...\n")
            execvp(command[0], command);
            free(command);
            fprintf(stderr, "Unable to exec: %s\n", strerror(errno));
            _exit(EXIT_FAILURE);
            break;
        default:
            t1.tv_sec = Timeout;
            t1.tv_nsec = 0;
            debug("Sleeping for %d seconds...\n", (int)t1.tv_sec);
            if (nanosleep(&t1, NULL) == 0)
            {
                debug("Killing child %d...\n", (int)t1.tv_sec);
                int k = kill(pid, SIGKILL);
                if (k < 0)
                {
                    fprintf(stderr, "Kill signal failed: %s\n", strerror(errno));
                    free(command);
                    exit(EXIT_FAILURE);                                                               
                }
             
                fprintf(stderr, "Nanosleep failed: %s\n", strerror(errno));
                free(command);
            }
            debug("Grabbing end time...\n");
            if (clock_gettime(CLOCK_MONOTONIC, &end) < 0)
            {
                fprintf(stderr, "GetTime Failed: %s\n", strerror(errno));
                free(command);
                return EXIT_FAILURE;
                                                                
            }
            double sec = end.tv_sec - start.tv_sec;
            double nsec = 0;
            nsec = (end.tv_nsec - start.tv_nsec)/BILLION;
            if (nsec < 0) nsec++;
            sec += nsec;

            debug("Waiting for child %d...\n", pid);
            w = wait(&status);
            if (w < 0)
            {
                fprintf(stderr, "Wait failed: %s\n", strerror(errno));
                free(command);
                return EXIT_FAILURE;        
            }

            int s;
            if (WIFEXITED(status))
            {
                s = WEXITSTATUS(status);
                    
            }
            else 
            {
                s = WTERMSIG(status);
            
            }
            debug("Child exit status: %d\n", s);
            if (command && s == 0)
            {
                free(command);
            }
            printf("Time Elapsed: %.1f\n", sec);

            return s;
            break;

    }

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
