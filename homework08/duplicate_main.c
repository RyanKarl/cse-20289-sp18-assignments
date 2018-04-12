/* duplicate_main.c: Main Execution */

#include "duplicate.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

/* Main Execution */

int         main(int argc, char *argv[]) {

    char *std_input = "/dev/stdin";
    char *std_output = "/dev/stdout";
    Options options = {std_input, std_output, INT_MAX, DEFAULT_BYTES, 0, 0};

    if(parse_options(argc, argv, &options)){
        int rfd = open(options.input_file, O_RDONLY);
        if(rfd < 0){
            fprintf(stderr, "Unable to open %s: %s\n", options.input_file, strerror(errno));
        return EXIT_FAILURE;
        }
        
        int wfd = open(options.output_file, O_CREAT | O_WRONLY, 0644);
        if(wfd < 0){
             fprintf(stderr, "Unable to open %s: %s\n", options.output_file, strerror(errno));
        return EXIT_FAILURE;         
        }

        if(options.skip){
            if(lseek(rfd, options.skip*options.bytes, SEEK_SET) < 0){
                fprintf(stderr, "Unable to open %s: %s\n", options.input_file, strerror(errno));
                    return EXIT_FAILURE;
            }
        }

            if(options.seek){
                if(lseek(wfd, options.seek*options.bytes, SEEK_SET) < 0){
                    fprintf(stderr, "Unable to open %s: %s\n", options.output_file, strerror(errno));
                    return EXIT_FAILURE;     
                }

            }

        char *buffer = malloc(options.bytes);
        if(!buffer){
            free(buffer);
            close(rfd);
            close(wfd);
            return EXIT_FAILURE;
        }

        int count = 0;
        int nread;

        while ((nread = read(rfd, buffer, options.bytes)) > 0 && options.count > count){
         
            int nwritten = write(wfd, buffer, nread);
            while (nwritten != nread) {
                nwritten += write(wfd, buffer + nwritten, nread - nwritten);
            }
            count++;
        }

        free(buffer);
        close(rfd);
        close(wfd);
        return EXIT_SUCCESS;

    }

    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
