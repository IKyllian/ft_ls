#include "ft_ls.h"

t_dirInfos *get_lstLast(t_dirInfos **dirList) {
	t_dirInfos *list = *dirList;

	while (list->next)
		list = list->next;
	return list;
}

t_dirInfos *ft_lstadd(t_dirInfos **dirList, struct stat dirStat, char dirName[256], char *path, int isSubdir, int *isFirstDir) {
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

	if (*dirList == NULL) {
		*dirList = new;
		*isFirstDir = 0;
		return (*dirList);
	 } else if (*isFirstDir) {
		list->subDir = new;
		*isFirstDir = 0;
		return (new);
	}
	while (list) {
		if (strcmp(dirName, list->dirName) < 0) {
			new->next = list;
			last->next = new;
			return (new);
		}
		last = list;
		list = list->next;
	}
	last->next = new;
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
				return i;
			}
			j++;
		}
		j = 0;
		isFlag = 0;
		i++;
	}
	return i;
}

// void fillArrayFolders(char ***folders, char *str) {
// 	if ((*folders) == NULL) {
// 		(*folders) = (char **)malloc(sizeof(char *) * 2);
// 		(*folders)[0] = ft_strdup(str);
// 		(*folders)[1] = NULL;
// 	} else {
// 		int length = arrayLength((*folders));
// 		char **tmp = (char **)malloc(sizeof(char *) * (length + 2));
// 		int i = 0;
// 		while ((*folders)[i]) {
// 			tmp[i] = ft_strdup((*folders)[i]);
// 			free((*folders)[i]);
// 			i++;
// 		}
// 		tmp[i] = ft_strdup(str);
// 		i++;
// 		tmp[i] = NULL;
// 		if ((*folders))
// 			free((*folders));
// 		(*folders) = tmp;
// 	}
// }

void printLongFormat(struct stat statBuffer) {
	struct group *myGroup;

	myGroup = getgrgid(statBuffer.st_gid);
	if (myGroup == NULL) {
		printf("Error or not found while Getgrgid\n");
		free(myGroup);
		exit(-1);
	}
	printf("%i ", statBuffer.st_nlink);
	if (myGroup->gr_mem[0])
		printf("%s ", myGroup->gr_mem[0]);
	printf("%s ", myGroup->gr_name);
	printf("%lli ", statBuffer.st_size);
}

t_dirInfos *readFolder(t_options options, char *path, int isSubdir, t_dirInfos **dirList) {
	DIR *pDir;
	struct dirent *currentDir;
	struct stat statBuffer;
	int isFirstDir = 1;
	t_dirInfos *list = *dirList;
	t_dirInfos *ret;
	
	char *firstStr = ft_strjoin(path, "/");
	char *str = NULL;

	pDir = opendir(path);

	if (pDir == NULL) {
		printf("Error while open\n");
		exit(-1);
	}

	while((currentDir = readdir(pDir)) != NULL) {
		if (str)
			free(str);
		str = ft_strjoin(firstStr, currentDir->d_name); // Check retour erreur strjoin
		if (stat(str, &statBuffer) < 0) {
			printf("Error while Stat\n");
			exit(-1);
		}
		if (isSubdir && isFirstDir) {
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir);
			list = list->subDir;
		} else {
			ret = ft_lstadd(&list, statBuffer, currentDir->d_name, str, isSubdir, &isFirstDir);
		}

		if (options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			readFolder(options, str, 1, &ret);
		}
	}
	closedir(pDir);
	return (list);
}

void printList(t_dirInfos **dirList, t_options options, int isSub) {
	t_dirInfos *list = *dirList;
	t_dirInfos *head = *dirList;

	if (isSub) {
		printf("\n%s:\n", list->path);
		list = list->subDir;
		head = head->subDir;
	}

	while (list) {
		if (options.longFormat)
			printLongFormat(list->dirStat);
		printf("%s \n", list->dirName);
		list = list->next;
	}

	while (head) {
		if (head->subDir)
			printList(&head, options, 1);
		head = head->next;
	}
}

int main(int ac, char **av) {	
	t_options options;
	int pathIndex = 1;

	t_dirInfos *dirList = NULL;

	options.longFormat = 0;
	options.reverse = 0;
	options.showHidden = 0;
	options.listSubdir = 0;
	if (ac > 1) {
		pathIndex = parser(av, &options);
	}

	dirList = readFolder(options, av[pathIndex], 0, &dirList);

	printList(&dirList, options, 0);

    return (0);
}