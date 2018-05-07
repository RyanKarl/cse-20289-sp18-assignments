 #include <errno.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include <netdb.h>
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <unistd.h>

 const char *HOST = "xavier.h4x0r.space";
        int MINPORT = 9000;
        int MAXPORT = 9999;

   void scan_port(const char *host, const char *port) {
        /* Lookup server address information */
        struct addrinfo *results;
        struct addrinfo  hints = {
                .ai_family   = AF_UNSPEC,   /* Return IPv4 and IPv6 choices */
                .ai_socktype = SOCK_STREAM, /* Use TCP */

        };

        int status;
        if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
                fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
        }

        /* For each server entry, allocate socket and try to connect */
        int client_fd = -1;
        for (struct addrinfo *p = results; p != NULL && client_fd < 0; p = p->ai_next) {
                /* Allocate socket */
                if ((client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
                        fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
                                continue;
                }

                /* Connect to host */
                if (connect(client_fd, p->ai_addr, p->ai_addrlen) < 0) {
                        close(client_fd);
                        client_fd = -1;
                        continue;
                } else {
                        printf("Connected successfully to %s:%s\n",host,port);
                }

        }

        /* Release allocate address information */
        freeaddrinfo(results);

        /* Open file stream from socket file descriptor */
        close(client_fd);

   }

int main(int argc, char *argv[]) {
        /* Connect to remote machine */
        int counter = MAXPORT-MINPORT;
        char buffer[BUFSIZ];
        for (int i = 0; i <= counter; i++){
                sprintf(buffer,"%d",i+9000);
                scan_port(HOST,buffer);

        }

        return EXIT_SUCCESS;

}




