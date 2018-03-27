/* huff.c */

#include "tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

typedef enum {
    TSV,
    CSV,
    YAML,
    JSON,
} Format;

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
    fprintf(stderr, "Flags:\n\n");
    fprintf(stderr, "    -f FORMAT    Output format (tsv, csv, yaml, json)\n");

    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */

    /* Process each file */
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
