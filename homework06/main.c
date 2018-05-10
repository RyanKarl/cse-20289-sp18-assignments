/* main.c: string library utility */

#include "str.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char *PROGRAM_NAME = NULL;

/* Modes */

enum {
    /* TODO: Enumerate Modes */
    STRIP = 1,
    REVERSE = 1 << 1,
    LOWER = 1 << 2,
    UPPER = 1 << 3,
    STARTSWITH = 1 << 4,
    ENDSWITH = 1 << 5

};

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s SOURCE TARGET\n\n", PROGRAM_NAME);
    fprintf(stderr, "Post Translation filters:\n\n");
    fprintf(stderr, "   -s          Strip whitespace\n");
    fprintf(stderr, "   -r          Reverse line\n");
    fprintf(stderr, "   -l          Convert to lowercase\n");
    fprintf(stderr, "   -u          Convert to uppercase\n");
    fprintf(stderr, "   -t FILTER   Only include lines that start with FILTER\n");
    fprintf(stderr, "   -d FILTER   Only include lines that end with FILTER\n");
    exit(status);
}

void translate_stream(FILE *stream, char *source, char *target, char *filter, int mode) {
    /* TODO: Process each line in stream by performing transformations */

    char line[BUFSIZ];
    char* newline;
    while(fgets(line, BUFSIZ, stream)){
        newline = line;
        newline = str_chomp(line);
        newline = str_translate(newline, source, target);

        if (mode & STRIP){
            newline = str_strip(newline);   
        };
        if (mode & REVERSE){
            newline = str_reverse(newline);      
        };
        if (mode & LOWER){
            newline = str_lower(newline);   
        };
        if (mode & UPPER){
            newline = str_upper(newline);   
        };
        if (mode & STARTSWITH){
            if (!str_startswith(newline, filter)){
                continue;
            }
        };
        if (mode & ENDSWITH){
            if (!str_endswith(newline, filter)){
                continue;
            }  
        };
    printf("%s\n", newline);
    }
}
/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */
    PROGRAM_NAME = argv[0];
    char *filter = NULL;
    char *source = NULL;
    char *target = NULL;
    int mode = 0;
       /* Parse command line arguments */

       for(int i = 1; i < argc; ++i) {
            char *arg = argv[i];
            if(strcmp(arg, "-s") == 0) {
                mode |= STRIP;
            } else if(strcmp(arg, "-r") == 0) {
                mode |= REVERSE;             
            } else if(strcmp(arg, "-t") == 0) {
                mode |= STARTSWITH;
                filter = argv[i + 1];
                ++i;
            } else if(strcmp(arg, "-d") == 0) {
                mode |= ENDSWITH;
                filter = argv[i + 1];
                i++;
            } else if(strcmp(arg, "-l") == 0) {
                mode |= LOWER;
            } else if(strcmp(arg, "-u") == 0) {
                mode |= UPPER;
            } else if(strcmp(arg, "-h") == 0) {
                usage(0);
            } else {
                source = argv[i];
                target = argv[i + 1];
                break;
            }
       }
    /* TODO: Translate Stream */
    translate_stream(stdin, source, target, filter, mode);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
