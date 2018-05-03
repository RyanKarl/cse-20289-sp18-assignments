/* grep.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s PATTERN FILE...\n", PROGRAM_NAME);    
    exit(status);
}

void cat_stream(FILE *stream, char *pattern) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stream)) {
        if(strstr(buffer, pattern))
                fputs(buffer, stdout);
    }
}

void cat_file(const char *path, char *pattern) {
    FILE *fs = fopen(path, "r");
    if (fs == NULL) {
        fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
        return;
    }
    cat_stream(fs, pattern);
    fclose(fs);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int argind = 1;

    /* Parse command line arguments */
    PROGRAM_NAME = argv[0];
    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }  
    }

    if (argind == argc)
            usage(1);
    char *pattern = argv[argind++];

    /* Process each file */
    if (argind == argc) {
        cat_stream(stdin, pattern);
    } else {
        while (argind < argc) {
            char *path = argv[argind++];
            if (strcmp(path, "-") == 0) {
                cat_stream(stdin, pattern);
            } else {
                cat_file(path, pattern);
            }
        }
    }

    return EXIT_SUCCESS;
}
