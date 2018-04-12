/* search_main.c: Main Execution */
#include "search.h"
/* Main Execution */ int main(int argc, char *argv[]) {
    /* Parse options */
    char * root = argv[1];
    char **r = &root;
    Options options = {-1, -1, false, "", "", -1, -1, -1, -1};
    bool po = options_parse(argc, argv, r, &options);
    if (!po) return EXIT_FAILURE;
    /* Check root */
    bool f = filter(root, &options);
    if (f) return EXIT_FAILURE;
    /* Walk root */
    if (!f)
    {
        printf("%s\n", options.path);
        int w = walk(root, &options);
        if (!w) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
