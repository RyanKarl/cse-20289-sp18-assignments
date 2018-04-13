/* search_utilities.c: Utilities */
#include "search.h" 
#include <errno.h> 
#include <dirent.h>
/* Utility Functions */ /**
 * Checks whether or not the directory is empty.
 * @param path Path to directory.
 * @return Whether or not the path is an empty directory.
 */ bool is_directory_empty(const char *path) {
    
        DIR *d = opendir(path);
        if (d == NULL){
            fprintf(stderr, strerror(errno));
            return 0;
        } //return false;
        struct dirent *e;
        int n = 0;
        while((e = readdir(d)) != NULL)
        {
            if (++n > 2) break;
        } 
        closedir(d);
        if (n <= 2) return true;
        return false;
}
/**
 * Retrieves modification time of file.
 * @param path Path to file.
 * @return The modification time of the file.
 */ time_t get_mtime(const char *path) {
        struct stat s;
        int checkTime = lstat(path, &s);
        if (checkTime < 0){ 
            fprintf(stderr, strerror(errno));
            return -1;
        }
        time_t t = s.st_mtime;
    
        return t;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
