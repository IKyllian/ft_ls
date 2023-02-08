#ifndef FT_LS
#define FT_LS

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
	int isSubdir;
	blkcnt_t blocksSize;
	struct s_dirInfos *subDir;
	struct s_dirInfos *next;
}	t_dirInfos;

int charIsFlag(char c);
int arrayLength(char **array);
void fillOptions(char c, t_options *options);
int isUntrackFolder(char *str);
int ishiddenFolder(char *str);

#endif