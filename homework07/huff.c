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

void print_node(Node *n, char * encoding, void *arg){
    if (n == NULL){
        return;
    }
    if((Format)arg == TSV){
        printf("%s\t%s\t%zu\n", n->symbol.string, encoding, n->count);
    }
    else if((Format)arg == CSV){
        printf("\"%s\",\"%s\",%zu\n", n->symbol.string, encoding, n->count);
    }
    else if((Format)arg == YAML){
        printf("\"%s\": {\"encoding\": \"%s\", \"count\": %zu}\n", n->symbol.string, encoding, n->count);
    }
    else if((Format)arg == JSON){
        printf("  \"%s\": {\"encoding\": \"%s\", \"count\": %zu},\n", n->symbol.string, encoding, n->count);
    }
    else{
        printf("\t%s%s\t%zu\n", n->symbol.string, encoding, n->count);
    }
    
}

void huff_stream(FILE *stream, Format f){
    Tree *t = tree_create();
    tree_build(t, stream);
    if(f == JSON){
        printf("{\n");
    }
    tree_walk(t, (NodeFunc)print_node, (void *)f);
    if(f == JSON){
         printf("}\n");
    }
    tree_delete(t);

}

void huff_file(const char *path, Format f){
    FILE *fs = fopen(path, "r");
    if(fs == NULL){
        fprintf(stderr, "%s: %s %s\n", PROGRAM_NAME, path, strerror(errno));
        return;
    }
    huff_stream(fs, f);
    fclose(fs);
}


/* Main Execution */

int main(int argc, char *argv[]) {
    
    int argind = 1;
    Format f = TSV;
    char *form;
   /* Parse command line arguments */
        while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
            char *arg = argv[argind++];
            switch (arg[1]) {
                case 'h':
                    usage(0);
                    break;
                case 'f':
                    form = argv[argind++];
                    if(strcmp("tsv", form) == 0) f = TSV;
                    else if(strcmp("csv", form) == 0) f = CSV;
                    else if(strcmp("yaml", form) == 0) f = YAML;
                    else if(strcmp("json", form) == 0) f = JSON;
                    break;
                default:
                    usage(1);
                    break;
                                                                                                                
            }              
        }

    /* Process each file */
        if(argind == argc){
            huff_stream(stdin, f);
        } else{
            while (argind < argc){
                char *path = argv[argind++];
                if(strcmp(path, "-") == 0){
                    huff_stream(stdin, f);
                } else{
                    huff_file(path, f);
                }
            }
        }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
