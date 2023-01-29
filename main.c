#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_options {
	int reverse;
	int showHidden;
}	t_options;

int charIsFlag(char c) {
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	return (0);
}


void fillOptions(char c, t_options *options) {
	if (c == 'r')
		options->reverse = 1;
	else if (c == 'a')
		options->showHidden = 1;
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

int main(int ac, char **av) {
	DIR *pDir;
	struct dirent *currentDir;
	t_options options;
	int pathIndex = 1;

	if (ac > 1) {
		pathIndex = parser(av, &options);
	}

	pDir = opendir(av[pathIndex]);

	if (pDir == NULL) {
		printf("Error while open\n");
		return (-1);
	}
	
	while((currentDir = readdir(pDir)) != NULL) {
		printf("%s \n", currentDir->d_name);
	}

	closedir(pDir);

    return (0);
}