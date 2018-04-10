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
    return false;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
