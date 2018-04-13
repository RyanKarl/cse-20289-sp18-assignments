/* search_utilities.c: Utilities */
#include "search.h" 
#include <errno.h> 
#include <dirent.h>
/* Utility Functions */ /**
 * Checks whether or not the directory is empty.
 * @param path Path to directory.
 * @return Whether or not the path is an empty directory.
 */ bool is_directory_empty(const char *path) {
    /*struct stat s;
    int checkS = stat(path, &s);
    if (checkS < 0) return false;
    if (s.st_size == 0) return true;*/
    DIR *d = opendir(path);
    if (d == NULL) return true;
    struct dirent *e;
    int n = 0;
    while((e = readdir(d)) != NULL)
    {
        if (++n > 2) break;
    } 
    closedir(d);
    if (n <= 2) return true;
    return false;
    // if cannot open, assume not empty
}
/**
 * Retrieves modification time of file.
 * @param path Path to file.
 * @return The modification time of the file.
 */ time_t get_mtime(const char *path) {
    //char buffer[BUFSIZ];
    struct stat s;
    int checkTime = lstat(path, &s);
    if (checkTime < 0) return EXIT_FAILURE;
    time_t t = s.st_mtime;
    
    return t;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
