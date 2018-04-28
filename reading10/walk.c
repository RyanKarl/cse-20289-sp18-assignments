/* walk.c *-------------------------------------------------------------------*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *path = argc > 1 ? argv[1] : ".";
    DIR  *d    = opendir(path);

    if (d == NULL) {
    	fprintf(stderr, "Unable to opendir %s: %s\n", path, strerror(errno));
	return EXIT_FAILURE;
    }

    struct dirent *e;
    while ((e = readdir(d))) {
    	if (strcmp(".", e->d_name) == 0 || strcmp("..", e->d_name) == 0 || e->d_type != DT_REG)
    	    continue;

        struct stat s;
        if (stat(e->d_name, &s) < 0) {
                fprintf(stderr, "%s", strerror(errno));
         }

    printf("%s %ld\n", e->d_name, s.st_size);
    
    //puts(e->d_name);
    }
    closedir(d);
    return EXIT_SUCCESS;
}

