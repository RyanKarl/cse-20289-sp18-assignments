#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

//const char *HOST = "example.com";
const char *HOST = "xavier.h4x0r.space";
const char *PORT = "9507";

FILE *socket_dial(const char *host, const char *port) {
        /* Lookup server address information */
        struct addrinfo *results;
        struct addrinfo  hints = {
                .ai_family   = AF_UNSPEC,   /* Return IPv4 and IPv6 choices */
                .ai_socktype = SOCK_STREAM, /* Use TCP */

            };

        int status;
        if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
                fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
                return NULL;

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

                }

        }

        /* Release allocate address information */
        freeaddrinfo(results);

        if (client_fd < 0) {
                fprintf(stderr, "Unable to connect to %s:%s: %s\n", host, port, strerror(errno));
                return NULL;

        }

        /* Open file stream from socket file descriptor */
        FILE *client_file = fdopen(client_fd, "w+");
        if (client_file == NULL) {
                fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
                close(client_fd);
                return NULL;

        }

        return client_file;

}

int main(int argc, char *argv[]) {
        /* Connect to remote machine */
        FILE *client_file = socket_dial(HOST, PORT);
        if (client_file == NULL) {
                            return EXIT_FAILURE;

            }

        // send stuff to the server, to spidey
        fprintf(client_file, "GET / HTTP/1.0\r\n");  // method line
        fprintf(client_file, "Host: %s\r\n", HOST); //  headers
        fprintf(client_file, "\r\n"); // blank line

        // read back response
        char buffer[BUFSIZ];
        while (fgets(buffer, BUFSIZ, client_file))
        {
                fputs(buffer, stdout);
        }

        fclose(client_file);
        return EXIT_SUCCESS;
}


