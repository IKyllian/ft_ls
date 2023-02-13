#include "ft_ls.h"

void printLongFormat(t_dirInfos *dir, int size[SIZE_LENGTH]) {
	char	permisions[SIZE_PERM];
	char	*dirTime;
	int		i;

	i = 0;
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

void printList(t_dirInfos **dirList, t_datas *datas, int isSub) {
	t_dirInfos	*list;
	t_dirInfos	*head;

	list = *dirList;
	head = *dirList;
	if (isSub) {
		printf("\n%s:\n", list->path);
		list = list->subDir;
		head = head->subDir;
	}
	if (datas->options.longFormat && list) {
		printf("total %lli\n", list->blocksSize);
	}

	while (list) {
		if (datas->options.longFormat)
			printLongFormat(list, datas->size);
		if (S_ISDIR(list->dirStat.st_mode))
			printf("%s%s%s \n", COLOR_CYAN, list->dirName, COLOR_DEFAULT);
		else
			printf("%s \n", list->dirName);
		list = list->next;
	}

	while (head) {
		if (head->subDir)
			printList(&head, datas, 1);
		head = head->next;
	}
}