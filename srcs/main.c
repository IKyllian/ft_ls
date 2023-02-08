#include "ft_ls.h"

void resetColor() {
  printf("\033[0m");
}

void blueColor() {
  printf("\033[1;36m");
}

void freeLst(t_dirInfos **dirList) {
	t_dirInfos *list = *dirList;
	t_dirInfos *next;

	while (list) {
		if (list->subDir) {
			freeLst(&list->subDir);
		}
		if (list->path)
			free(list->path);
		if (list->dirName)
			free(list->dirName);
		next = list->next;
		free(list);
		list = next;
	}
}

t_dirInfos *ft_lstadd(t_dirInfos **dirList, struct stat dirStat, char dirName[256], char *path, int isSubdir, int *isFirstDir, int isReverse, t_dirInfos **dirParent) {
	t_dirInfos *list = *dirList;
	t_dirInfos *last  = NULL;
	t_dirInfos *new  = NULL;

	new = (t_dirInfos *)malloc(sizeof(t_dirInfos));
	new->dirName = ft_strdup(dirName);
	new->path = ft_strdup(path);
	new->dirStat = dirStat;
	new->isSubdir = isSubdir;
	new->subDir = NULL;
	new->next = NULL;
	new->blocksSize = 0;
	(void)isReverse;

	if (*dirList == NULL) {
		new->blocksSize += dirStat.st_blocks;
		*dirList = new;
		*isFirstDir = 0;
		return (*dirList);
	 } else if (*isFirstDir) {
		new->blocksSize += dirStat.st_blocks;
		list->subDir = new;
		*isFirstDir = 0;
		return (new);
	}
	while (list) {
		if ((!isReverse && strcmp(dirName, list->dirName) < 0) || (isReverse && strcmp(dirName, list->dirName) > 0)) {
			new->next = list;
			if (last != NULL)
				last->next = new;
			else {
				new->blocksSize = list->blocksSize;
				new->blocksSize += new->dirStat.st_blocks;
				if (*dirParent)
					(*dirParent)->subDir = new;
				*dirList = new;
				return (new);
			}
			(*dirList)->blocksSize += new->dirStat.st_blocks;
			return (new);
		}
		last = list;
		list = list->next;
	}
	last->next = new;
	(*dirList)->blocksSize += new->dirStat.st_blocks;
	return (new);
}

int parser(char **av, t_options *options) {
	int i = 1;
	int j = 0;
	int isFlag = 0;
	while (av[i]) {
		while (av[i][j]) {
			if (j == 0 && av[i][j] == '-') {
				isFlag = 1;
			} else if (isFlag) {
				if (!charIsFlag(av[i][j])) {
					printf("ft_ls : invalid option -- %c\n", av[i][j]);
					printf("usage: ls [-Ralrt] [file ...] \n");
					return (-1);
				}
				fillOptions(av[i][j], options);
			} else {
				return (i);
			}
			j++;
		}
		j = 0;
		isFlag = 0;
		i++;
	}
	return (-1);
}

// char *dateFormat(char *date) {
// 	char *newFormat;
// 	int i = 0;
// 	int length = 0;
// 	int space = 0;

// 	while (date[i]) {
// 		if (date[i] = ' ')
// 			space++;
// 		if (space == 1)
// 			length
// 		i++;
// 	}

// }

void setPermision(struct stat dirStat, char **str) {
	if (S_ISDIR(dirStat.st_mode))
		(*str)[0] = 'd';
	if (dirStat.st_mode & S_IRUSR )
        (*str)[1] = 'r';
    if (dirStat.st_mode & S_IWUSR )
        (*str)[2] = 'w';
    if (dirStat.st_mode & S_IXUSR )
        (*str)[3] = 'x';

    if (dirStat.st_mode & S_IRGRP )
        (*str)[4] = 'r';
    if (dirStat.st_mode & S_IWGRP )
        (*str)[5] = 'w';
    if (dirStat.st_mode & S_IXGRP )
        (*str)[6] = 'x';

    if (dirStat.st_mode & S_IROTH )
        (*str)[7] = 'r';
    if (dirStat.st_mode & S_IWOTH )
        (*str)[8] = 'w';
    if (dirStat.st_mode & S_IXOTH )
    	(*str)[9] = 'x';
}

void printLongFormat(struct stat statBuffer) {
	struct group *groupInfos;
	struct passwd *ownerInfos;
	char *permisions;
	char *dirTime;

	permisions = (char *)malloc(sizeof(char) * 11);
	int i = 0;
	while (i < 10) {
		permisions[i] = '-';
		i++;
	}
	permisions[i] = '\0';

	setPermision(statBuffer, &permisions);
	groupInfos = getgrgid(statBuffer.st_gid);
	ownerInfos = getpwuid(statBuffer.st_uid);
	dirTime = ctime(&statBuffer.st_mtimespec.tv_sec);
	if (groupInfos == NULL) {
		printf("Error or not found while Getgrgid\n");
		free(groupInfos);
		exit(-1);
	}
	printf("%s ", permisions);
	printf("%i ", statBuffer.st_nlink);
	printf("%s ", ownerInfos->pw_name);
	printf("%s ", groupInfos->gr_name);
	printf("%lli ", statBuffer.st_size);
	if (dirTime[ft_strlen(dirTime) - 1] == '\n')
		dirTime[ft_strlen(dirTime) - 1] = '\0';
	printf("%s ", dirTime);
}

void printList(t_dirInfos **dirList, t_options options, int isSub) {
	t_dirInfos *list = *dirList;
	t_dirInfos *head = *dirList;

	if (isSub) {
		printf("\n%s:\n", list->path);
		list = list->subDir;
		head = head->subDir;
	}
	if (options.longFormat && list) {
		printf("total %lli\n", list->blocksSize);
	}

	while (list) {
		if (options.longFormat)
			printLongFormat(list->dirStat);
		if (S_ISDIR(list->dirStat.st_mode))
			blueColor();
		printf("%s \n", list->dirName);
		if (S_ISDIR(list->dirStat.st_mode))
			resetColor();
		list = list->next;
	}

	while (head) {
		if (head->subDir)
			printList(&head, options, 1);
		head = head->next;
	}
}

void printDebug(t_dirInfos **dirList) {
	t_dirInfos *list = *dirList;

	printf("\n DEBUG:\n");
	while (list) {
		printf("%s \n",list->dirName);
		list = list->next;
	}
	printf("\n");
}

t_dirInfos *readFolder(t_options options, char *path, int isSubdir, t_dirInfos **dirList) {
	DIR *pDir;
	struct dirent *currentDir;
	struct stat statBuffer;
	int isFirstDir = 1;
	t_dirInfos *list = *dirList;
	t_dirInfos *ret;
	t_dirInfos *dirParent = NULL;
	char *str = NULL;
	char *firstStr;

	if (path && path[ft_strlen(path) - 1] == '/')
		firstStr = ft_strjoin(path, NULL);
	else
		firstStr = ft_strjoin(path, "/");

	pDir = opendir(path);

	if (pDir == NULL) {
		printf("Error while open\n");
		exit(-1);
	}

	while((currentDir = readdir(pDir)) != NULL) {
		if (!options.showHidden && ishiddenFolder(currentDir->d_name))	{
			continue;
		}
		str = ft_strjoin(firstStr, currentDir->d_name); // Check retour erreur strjoin
		if (stat(str, &statBuffer) < 0) {
			printf("Error while Stat\n");
			if (firstStr)
				free(firstStr);
			if (str)
				free(str);
			exit(-1);
		}
	
		if (isSubdir && isFirstDir) {
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, options.reverse, &dirParent);
			dirParent = list;
			list = list->subDir;
		} else {
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, options.reverse, &dirParent);
		}
		if (options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			readFolder(options, str, 1, &ret);
		}
		if (str)
			free(str);
	}
	if (firstStr)
		free(firstStr);
	closedir(pDir);
	return (list);
}

int main(int ac, char **av) {	
	t_options options;
	int pathIndex = -1;
	t_dirInfos *dirList = NULL;

	options.longFormat = 0;
	options.reverse = 0;
	options.showHidden = 0;
	options.listSubdir = 0;
	if (ac > 1) {
		pathIndex = parser(av, &options);
	}

	if (pathIndex > 0) {
		dirList = readFolder(options, av[pathIndex], 0, &dirList);
	} else {
		dirList = readFolder(options, ".", 0, &dirList);
	}

	printList(&dirList, options, 0);
	freeLst(&dirList);

    return (0);
}