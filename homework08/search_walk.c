/* search_walk.c: Walk */
#include "search.h" 
#include <errno.h> 
#include <dirent.h>
/* Walk Functions */ /**
 * Recursively walk the root directory with specified options.
 * @param root Root directory path.
 * @param options User specified filter options.
 * @return Whether or not walking this directory was successful.
 */ int walk(const char *root, const Options *options) {
    DIR *d = opendir(root);
    if (d == NULL) {
        fprintf(stderr, "Unable to opendir %s: %s\n", root, strerror(errno));
        return EXIT_FAILURE;
    }
    struct dirent *e;
    while ((e = readdir(d))) {
        if (!streq(".", e->d_name) && !streq("..", e->d_name) && e->d_type == DT_REG)
        {
            char buffer[BUFSIZ];
            sprintf(buffer, root, e->d_name);
            walk(buffer, options);
            //if (w) printf("", e->d_name);
        }
        struct stat s;
        if (stat(e->d_name, &s) < 0) {
                fprintf(stderr, "%s", strerror(errno));
         }
        if (filter(root, options)) printf("%s\n", e->d_name);
    
    }
    closedir(d);
    return EXIT_SUCCESS;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
