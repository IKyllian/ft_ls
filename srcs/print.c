#include "ft_ls.h"

void	printLongFormat(t_dirInfos *dir, int size[SIZE_LENGTH])
{
	char	permisions[SIZE_PERM];
	char	*dirTime;
	int		i;

	i = 0;
	while (i < 10)
	{
		permisions[i] = '-';
		i++;
	}
	permisions[i] = '\0';
	setPermision(dir->dirStat, permisions);
	dirTime = ctime(&dir->dirStat.st_mtime) + 4;

	ft_printf("%s ", permisions);
	ft_printf("%*i ", size[0], dir->dirStat.st_nlink);
	ft_printf("%-*s ", size[1], dir->owner);
	ft_printf(" %-*s ", size[2], dir->gr_name);
	ft_printf(" %*i ", size[3], dir->dirStat.st_size);
	ft_printf("%.12s ", dirTime);
}

void	printDirInfos(int isSub, t_dirInfos **list, t_dirInfos	**head, t_datas *datas)
{
	if (isSub)
	{
		ft_printf("\n%s:\n", (*list)->path);
		(*list) = (*list)->subDir;
		(*head) = (*head)->subDir;
	}
	if (datas->options.longFormat && (*list))
	{
		ft_printf("total %i\n", (*list)->blocksSize);
	}
}

void	printList(t_dirInfos **dirList, t_datas *datas, int isSub)
{
	t_dirInfos	*list;
	t_dirInfos	*head;

	list = *dirList;
	head = *dirList;
	printDirInfos(isSub, &list, &head, datas);
	while (list)
	{
		if (datas->options.longFormat)
			printLongFormat(list, datas->size);
		// if (S_ISDIR(list->dirStat.st_mode))
		// 	ft_printf("%s%s%s \n", COLOR_CYAN, list->dirName, COLOR_DEFAULT);
		// else
			ft_printf("%s \n", list->dirName);
		list = list->next;
	}

	while (head)
	{
		if (head->subDir)
			printList(&head, datas, 1);
		head = head->next;
	}
}