#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include "ft_ls.h"

typedef struct s_options {
	int reverse;
	int showHidden;
	int longFormat;
	int listSubdir;
}	t_options;

int charIsFlag(char c) {
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	return (0);
}

int arrayLength(char **array) {
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void fillOptions(char c, t_options *options) {
	if (c == 'r')
		options->reverse = 1;
	else if (c == 'a')
		options->showHidden = 1;
	else if (c == 'l')
		options->longFormat = 1;
	else if (c == 'R')
		options->listSubdir = 1;
}

int isUntrackFolder(char *str) {
	if (ft_strlen(str) == 1 && str[0] == '.')
		return (1);
	else if (ft_strlen(str) == 2 && str[0] == '.' && str[1] == '.')
		return (1);
	return (0);
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

void fillArrayFolders(char ***folders, char *str) {
	if ((*folders) == NULL) {
		(*folders) = malloc(sizeof(char *) * 2);
		(*folders)[0] = ft_strdup(str);
		(*folders)[1] = NULL;
	} else {
		int length = arrayLength((*folders));
		char **tmp = malloc(sizeof(char *) * (length + 2));
		int i = 0;
		while ((*folders)[i]) {
			tmp[i] = ft_strdup((*folders)[i]);
			free((*folders)[i]);
			i++;
		}
		tmp[i] = ft_strdup(str);
		i++;
		tmp[i] = NULL;
		if ((*folders))
			free((*folders));
		(*folders) = tmp;
	}
}

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

void readFolder(t_options options, char *path, int isSubFolder) {
	DIR *pDir;
	struct dirent *currentDir;
	struct stat statBuffer;
	
	char *firstStr = ft_strjoin(path, "/");
	char *str = NULL;
	char **folders = NULL;

	pDir = opendir(path);

	if (pDir == NULL) {
		printf("Error while open\n");
		exit(-1);
	}
	if (isSubFolder)
		printf("\n%s:\n", path);
	while((currentDir = readdir(pDir)) != NULL) {
		if (str)
			free(str);
		str = ft_strjoin(firstStr, currentDir->d_name); // Check retour erreur strjoin
		if (stat(str, &statBuffer) < 0) {
			printf("Error while Stat\n");
			exit(-1);
		}
		if (options.longFormat) {
			printLongFormat(statBuffer);
		}
		printf("%s \n", currentDir->d_name);
		if (options.listSubdir && S_ISDIR(statBuffer.st_mode) && !isUntrackFolder(currentDir->d_name)) {
			fillArrayFolders(&folders, str);
		}
	}
	if (options.listSubdir && folders != NULL) {
		int i = 0;
		while (folders[i]) {
			readFolder(options, folders[i], 1);
			i++;
		}
	}
	closedir(pDir);
}

int main(int ac, char **av) {	
	t_options options;
	int pathIndex = 1;

	options.longFormat = 0;
	options.reverse = 0;
	options.showHidden = 0;
	options.listSubdir = 0;
	if (ac > 1) {
		pathIndex = parser(av, &options);
	}

	readFolder(options, av[pathIndex], 0);

    return (0);
}