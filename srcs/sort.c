#include "ft_ls.h"

int sortByLetter(t_dirInfos *new, t_dirInfos *list, int reverse)
{
    return ((!reverse && strcmp(new->dirName, list->dirName) < 0)
        || (reverse && strcmp(new->dirName, list->dirName) > 0));
}

int sortByTime(t_dirInfos *new, t_dirInfos *list, t_options	options)
{
    if (options.sortTime && new->dirStat.st_mtime == list->dirStat.st_mtime) {
        // if (new->dirStat.st_atime == list->dirStat.st_atime) {
        //     if (new->dirStat.st_ctime == list->dirStat.st_ctime)
                return (sortByLetter(new, list, !options.reverse));
        //    else
        //     return ((options.sortTime && !options.reverse && new->dirStat.st_ctime > list->dirStat.st_ctime)
        //         || (options.sortTime && options.reverse && new->dirStat.st_ctime < list->dirStat.st_ctime));
        // } else
        //     return ((options.sortTime && !options.reverse && new->dirStat.st_atime > list->dirStat.st_atime)
        //         || (options.sortTime && options.reverse && new->dirStat.st_atime < list->dirStat.st_atime));
    }   
    return ((options.sortTime && !options.reverse && new->dirStat.st_mtime > list->dirStat.st_mtime)
        || (options.sortTime && options.reverse && new->dirStat.st_mtime < list->dirStat.st_mtime));
}