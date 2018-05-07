/* duplicate_options.c: Options Parsing */

#include "duplicate.h"

/* Options Functions */

/**
 * Display usage message and exit.
 * @param   progname        Name of program.
 * @param   status          Exit status.
 */
void        usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options]\n\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "    if=FILE     Read from FILE instead of stdin\n");
    fprintf(stderr, "    of=FILE     Write to FILE instead of stdout\n");
    fprintf(stderr, "    count=N     Copy only N input blocks\n");
    fprintf(stderr, "    bs=BYTES    Read and write up to BYTES bytes at a time\n");
    fprintf(stderr, "    seek=N      Skip N obs-sized blocks at start of output\n");
    fprintf(stderr, "    skip=N      Skip N ibs-sized blocks at start of input\n");
    exit(status);
}

/**
 * Parse command-line options.
 * @param   argc            Number of command-line arguments.
 * @param   argv            Array of command-line arguments.
 * @param   options         Pointer to Options structure.
 * @return  Whether or not parsing the command-line options was successful.
 */
bool        parse_options(int argc, char **argv, Options *options) {
    int argind = 1;
    char *PROGRAM_NAME = argv[0];
    while(argind < argc && strlen(argv[argind])>1){
        char *arg = argv[argind++];
        if(streq("-h", arg)){
            usage(PROGRAM_NAME, 0);
        }

        else{
            char str[BUFSIZ];
            strcpy(str, arg);
            char *eq = strchr(arg, '=');
            *eq = '\0';
            eq++;
            
            if(streq(arg, "if"))
                options->input_file = eq;
            else if(streq(arg, "of"))
                options->output_file = eq;
            else if(streq(arg, "count")){
                long int num = strtol(eq, NULL, 10);
                options->count = num;
            }
            else if(streq(arg, "bs")){
                long int num = strtol(eq, NULL, 10);
                options->bytes = num;
            }
            else if(streq(arg, "seek")){
                long int num = strtol(eq, NULL, 10);
                options->seek = num;
            }
            else if(streq(arg, "skip")){
                long int num = strtol(eq, NULL, 10);
                options->skip = num;
            }
            else{
                usage(PROGRAM_NAME, 1);
            }
        }
    }
return true;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
