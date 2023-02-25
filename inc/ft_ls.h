#ifndef FT_LS
# define FT_LS

#ifdef __APPLE__
#ifndef st_mtime
# define st_mtime st_mtimespec.tv_sec
#endif
#endif

#ifdef __APPLE__
#ifndef st_atime
# define st_atime st_atimespec.tv_sec
#endif
#endif

#ifdef __APPLE__
#ifndef st_ctime
# define st_ctime st_ctimespec.tv_sec
#endif
#endif


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

typedef struct s_options {
	int reverse;
	int sortTime;
	int showHidden;
	int longFormat;
	int listSubdir;
}	t_options;

typedef struct s_subDir_infos {
	int		isSubDir;
	int		isFirstDir;
	char	*init_path;
}	t_subDir_infos;

typedef struct s_dirInfos {
	struct stat			dirStat;
	char				*dirName;
	char				*path;
	char				*owner;
	char				*gr_name;
	int					isSubdir;
	blkcnt_t			blocksSize;
	struct s_dirInfos	*subDir;
	struct s_dirInfos	*next;
}	t_dirInfos;

typedef struct s_heads_list {
	t_dirInfos *list;
	t_dirInfos *ret;
	t_dirInfos *dirParent;
} t_heads_list;

typedef struct s_datas {
	t_options	options;
	int			size[SIZE_LENGTH];
}	t_datas;

int		charIsFlag(char c);
int		arrayLength(char **array);
void	fillOptions(char c, t_options *options);
int		isUntrackFolder(char *str);
int		ishiddenFolder(char *str);

void	freeLst(t_dirInfos **dirList);
void	mem_check(void *pointer, t_dirInfos **dirList);

void	setPermision(struct stat dirStat, char str[SIZE_PERM]);
char	setFileType(mode_t mode);
void	setColumnSize(int size[SIZE_LENGTH], t_dirInfos *dir);

void	printLongFormat(t_dirInfos *dir, int size[SIZE_LENGTH]);
void	printList(t_dirInfos **dirList, t_datas *datas, int isSub);

void main_struct_init(t_datas *datas);
t_dirInfos *init_dirInfo(char dirName[256], char *path, int isSubdir);
t_subDir_infos init_subDir_infos(int isSubDir);

t_dirInfos	*ft_lstadd_first(int size[SIZE_LENGTH], t_heads_list *heads_list, t_dirInfos **new, t_subDir_infos *subDirInfos);
t_dirInfos	*ft_lstadd_second(t_dirInfos **new, t_heads_list *heads_list, t_options	options);

int parser(char **av, t_options *options);

t_dirInfos *readDir(t_datas *datas, char *path, int isSubdir, t_dirInfos **dirList);

int sortByLetter(t_dirInfos *new, t_dirInfos *list, int reverse);
int sortByTime(t_dirInfos *new, t_dirInfos *list, t_options	options);

#endif