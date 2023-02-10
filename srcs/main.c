#include "ft_ls.h"

int		integer_len(int n)
{
	int		len;

	len = 1;
	while (n / 10) {
		n /= 10;
		++len;
	}
	return (len);
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
		if (list->owner)
			free(list->owner);
		if (list->gr_name)
			free(list->gr_name);
		next = list->next;
		free(list);
		list = next;
	}
}

void setColumnSize(int size[SIZE_LENGTH], t_dirInfos *dir) {
	size[0] = MAX(integer_len(dir->dirStat.st_nlink), size[0]);
	size[1] = MAX(ft_strlen(dir->owner), size[1]);
	size[2] = MAX(ft_strlen(dir->gr_name), size[2]);
	size[3] = MAX(integer_len(dir->dirStat.st_size), size[3]);
}

t_dirInfos *ft_lstadd(t_dirInfos **dirList, struct stat dirStat, char dirName[256], char *path, int isSubdir, int *isFirstDir, int isReverse, t_dirInfos **dirParent, int size[SIZE_LENGTH]) {
	t_dirInfos *list = *dirList;
	t_dirInfos *last  = NULL;
	t_dirInfos *new  = NULL;
	struct group *groupInfos;
	struct passwd *ownerInfos;

	groupInfos = getgrgid(dirStat.st_gid);

	if (groupInfos == NULL) {
		printf("Error or not found while Getgrgid\n");
		exit(-1);
	}
	ownerInfos = getpwuid(dirStat.st_uid);
	new = (t_dirInfos *)malloc(sizeof(t_dirInfos));
	new->dirName = ft_strdup(dirName);
	new->path = ft_strdup(path);
	new->owner = ft_strdup(ownerInfos->pw_name);
	new->gr_name = ft_strdup(groupInfos->gr_name);
	new->dirStat = dirStat;
	new->isSubdir = isSubdir;
	new->subDir = NULL;
	new->next = NULL;
	new->blocksSize = 0;

	setColumnSize(size, new);

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

char setFileType(mode_t mode) {
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

void setPermision(struct stat dirStat, char str[SIZE_PERM]) {

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

void printLongFormat(t_dirInfos *dir, int size[SIZE_LENGTH]) {
	char permisions[SIZE_PERM];
	char *dirTime;
	int i = 0;

	while (i < 10) {
		permisions[i] = '-';
		i++;
	}
	permisions[i] = '\0';
	setPermision(dir->dirStat, permisions);
	dirTime = ctime(&dir->dirStat.st_mtimespec.tv_sec) + 4;

	printf("%s ", permisions);
	printf("%*i ", size[0], dir->dirStat.st_nlink);
	printf("%-*s ", size[1], dir->owner);
	printf(" %-*s ", size[2], dir->gr_name);
	printf(" %*lli ", size[3], dir->dirStat.st_size);
	printf("%.12s ", dirTime);
}

void printList(t_dirInfos **dirList, t_options options, int isSub, int size[SIZE_LENGTH]) {
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
			printLongFormat(list, size);
		if (S_ISDIR(list->dirStat.st_mode))
			printf("%s%s%s \n", COLOR_CYAN, list->dirName, COLOR_DEFAULT);
		else
			printf("%s \n", list->dirName);
		list = list->next;
	}

	while (head) {
		if (head->subDir)
			printList(&head, options, 1, size);
		head = head->next;
	}
}

t_dirInfos *readFolder(t_options options, char *path, int isSubdir, t_dirInfos **dirList, int size[SIZE_LENGTH]) {
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
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, options.reverse, &dirParent, size);
			dirParent = list;
			list = list->subDir;
		} else {
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir, options.reverse, &dirParent, size);
		}
		if (options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			readFolder(options, str, 1, &ret, size);
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
	int size[SIZE_LENGTH];

	options.longFormat = 0;
	options.reverse = 0;
	options.showHidden = 0;
	options.listSubdir = 0;
	ft_bzero(size, sizeof(size));
	if (ac > 1) {
		pathIndex = parser(av, &options);
	}

	if (pathIndex > 0) {
		dirList = readFolder(options, av[pathIndex], 0, &dirList, size);
	} else {
		dirList = readFolder(options, ".", 0, &dirList, size);
	}

	printList(&dirList, options, 0, size);
	freeLst(&dirList);

    return (0);
}