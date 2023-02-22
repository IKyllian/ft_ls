#include "ft_ls.h"

void setPermision(struct stat dirStat, char str[SIZE_PERM])
{
	str[0] = setFileType(dirStat.st_mode);
	
	if (dirStat.st_mode & S_IRUSR )
        str[1] = 'r';
    if (dirStat.st_mode & S_IWUSR )
        str[2] = 'w';
    if (dirStat.st_mode & S_IXUSR )
        str[3] = 'x';

    if (dirStat.st_mode & S_IRGRP )
        str[4] = 'r';
    if (dirStat.st_mode & S_IWGRP )
        str[5] = 'w';
    if (dirStat.st_mode & S_IXGRP )
        str[6] = 'x';

    if (dirStat.st_mode & S_IROTH )
        str[7] = 'r';
    if (dirStat.st_mode & S_IWOTH )
        str[8] = 'w';
    if (dirStat.st_mode & S_IXOTH )
    	str[9] = 'x';
}

char setFileType(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

void setColumnSize(int size[SIZE_LENGTH], t_dirInfos *dir)
{
	size[0] = MAX(integer_length(dir->dirStat.st_nlink), size[0]);
	size[1] = MAX(ft_strlen(dir->owner), size[1]);
	size[2] = MAX(ft_strlen(dir->gr_name), size[2]);
	size[3] = MAX(integer_length(dir->dirStat.st_size), size[3]);
}