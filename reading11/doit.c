/* walk.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <unistd.h>

/**
 * Run specified program with the bourne shell.
 * @param     command     Command to run.
 * @return    Exit status of child process.
 */
int doit(const char *command) {
    int rc = fork();
    if (rc < 0) { 
    fprintf(stderr, "fork failed\n");
        exit(1);
    } 

    if(rc == 0){

        execl("/bin/sh", "sh", "-c", command, NULL);
        return EXIT_FAILURE;
    } 

    else{
        
    int val;
    int wc = wait(&val);
    if (wc < 0){
            fprintf(stderr, "wait failed\n");
            return EXIT_FAILURE;
        }
    
    return WEXITSTATUS(val);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Usage: ./doit COMMAND");
        return EXIT_FAILURE;
    }
    return doit(argv[1]);

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
