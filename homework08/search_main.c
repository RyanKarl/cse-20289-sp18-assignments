/* search_main.c: Main Execution */
#include "search.h"
/* Main Execution */ int main(int argc, char *argv[]) {
    /* Parse options */
    char * root = argv[1];
    if (root == NULL){
        root = ".";
    }

    Options options = {0, 0, false, NULL, NULL, 0, 0, -1, -1};
    bool po = options_parse(argc, argv, &root, &options);
    if (!po) return EXIT_FAILURE;
    /* Check root */
    bool f = filter(root, &options);
    if (!f){
        printf("%s\n", root);
    } 
    /* Walk root */
    return walk(root, &options);
    
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
