#ifndef FT_LS
# define FT_LS

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <grp.h>
# include <string.h>
# include <time.h>
# include <pwd.h>
# include "libft.h"

# define SIZE_LENGTH 4
# define SIZE_PERM 11

# define COLOR_DEFAULT	"\033[0m"
# define COLOR_CYAN		"\033[1;36m"

# define MAX(a, b)	b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)	a & ((a - b) >> 31) | b & (~(a - b) >> 31)

typedef struct s_options {
	int reverse;
	int showHidden;
	int longFormat;
	int listSubdir;
}	t_options;

typedef struct s_dirInfos {
	struct stat dirStat;
	char *dirName;
	char *path;
	char *owner;
	char *gr_name;
	int isSubdir;
	blkcnt_t blocksSize;
	struct s_dirInfos *subDir;
	struct s_dirInfos *next;
}	t_dirInfos;

typedef struct s_datas {
	t_options options;
	int size[SIZE_LENGTH];
}	t_datas;

int charIsFlag(char c);
int arrayLength(char **array);
void fillOptions(char c, t_options *options);
int isUntrackFolder(char *str);
int ishiddenFolder(char *str);
int	integer_len(int n);

void freeLst(t_dirInfos **dirList);
void mem_check(void *pointer, t_dirInfos **dirList);

void setPermision(struct stat dirStat, char str[SIZE_PERM]);
char setFileType(mode_t mode);
void setColumnSize(int size[SIZE_LENGTH], t_dirInfos *dir);

void printLongFormat(t_dirInfos *dir, int size[SIZE_LENGTH]);
void printList(t_dirInfos **dirList, t_datas *datas, int isSub);

void main_struct_init(t_datas *datas);
t_dirInfos *init_dirInfo(struct stat dirStat, char dirName[256], char *path, int isSubdir);
t_dirInfos *ft_lstadd(t_dirInfos **dirList, struct stat dirStat, char dirName[256], char *path, int isSubdir, int *isFirstDir, int isReverse, t_dirInfos **dirParent, int size[SIZE_LENGTH]);


#endif