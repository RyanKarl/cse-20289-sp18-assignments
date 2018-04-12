/* search_filter.c: Filters */
#include "search.h" 
#include <errno.h> 
#include <string.h> 
#include <fnmatch.h> 
#include <unistd.h> 
#include <stdlib.h>
/* Internal Filter Functions */ bool filter_access(const char *path, const struct stat *stat, const Options *options) {
    return options->access && access(path, options->access) != 0;
}
bool filter_type(const char *path, const struct stat *stat, const Options *options) {
    return options->type && (stat->st_mode & S_IFMT) != options->type;
}
bool filter_empty(const char *path, const struct stat *stat, const Options *options) {
   if (options->empty){
        switch (stat->st_mode & S_IFMT){
            case S_IFREG: return stat->st_size != 0;
            case S_IFDIR: return !is_directory_empty(path);
            default:
                return true;
        }
    }
    return false;
}
bool filter_name(const char *path, const struct stat *stat, const Options *options) {
    return options->name && fnmatch(options->name, path, 0) != 0;
}
bool filter_path(const char *path, const struct stat *stat, const Options *options) {
    return options->path && fnmatch(options->path, path, 0) != 0;
}
bool filter_perm(const char *path, const struct stat *stat, const Options *options) {
    return options->perm && (stat->st_mode & ~S_IFMT) != options->perm;
}
bool filter_newer(const char *path, const struct stat *stat, const Options *options) {
    return options->newer && options->newer <= stat->st_mtime;
}
bool filter_uid(const char *path, const struct stat *stat, const Options *options) {
    return options->uid >= 0 && options->uid != stat->st_uid;
}
bool filter_gid(const char *path, const struct stat *stat, const Options *options) {
    return options->gid >= 0 && options->gid != stat->st_gid;
}
FilterFunc FILTER_FUNCTIONS[] = { /* Array of function pointers. */
    filter_access,
    filter_type,
    filter_empty,
    filter_name,
    filter_path,
    filter_perm,
    filter_newer,
    filter_uid,
    filter_gid,
    NULL,
};
/* External Filter Functions */ /**
 * Filter path based options.
 * @param path Path to file to filter.
 * @param options Pointer to Options structure.
 * @return Whether or not the path should be filtered out (false means include
 * it in output, true means exclude it from output).
 */ bool filter(const char *path, const Options *options) {
    printf("%s\n", path);
    struct stat s;
    int checkStat = lstat(path, &s);
    if (checkStat < 0) return true;
    for (int i = 0; i < 9; i++)
    {
        if (FILTER_FUNCTIONS[i](path, &s, options)) return true;
    }
    return false;
}
/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
