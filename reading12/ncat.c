/* walk.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>


void usage(int status) {
    fprintf(stderr, "Usage: ./ncat HOST PORT");    
    exit(status);
}

int main(int argc, char *argv[]) {
    /* Lookup server address information */
    struct addrinfo  hints = {}, *servinfo, *p;
        hints.ai_family    = AF_UNSPEC;   /* Return IPv4 and IPv6 choices */
        hints.ai_socktype  = SOCK_STREAM; /* Use TCP */ 

    /* Parse command line arguments */

    if (argc < 3){
        usage(1);
    }
    char *HOST = argv[1];
    char *PORT = argv[2];
    

    int sockfd;
    int status;
    if ((status = getaddrinfo(HOST, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "Could not look up %s:%s: %s\n", HOST, PORT, gai_strerror(status));
        return EXIT_FAILURE;
    }

    /* For each server entry, allocate socket and try to connect */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
                continue;
                                                
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) < 0) {
            close(sockfd);
            sockfd=-1;
            continue;                                                
        }
        
        break;                
}

    /* Release allocate address information */
    freeaddrinfo(servinfo);

    if (sockfd < 0) {
        fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT, strerror(errno));
            return EXIT_FAILURE;
    }

    printf("Connected to %s:%s\n", HOST, PORT);
    /* Open file stream from socket file descriptor */
    FILE *client_file = fdopen(sockfd, "r+");
    if (client_file == NULL) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    /* Read from stdin and send to server */
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stdin)) {
        fputs(buffer, client_file);
        fgets(buffer, BUFSIZ, client_file);
    }

    close(sockfd);

    return EXIT_SUCCESS;
}


/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
