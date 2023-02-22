#include "ft_ls.h"

void	freeLst(t_dirInfos **dirList)
{
	t_dirInfos	*list;
	t_dirInfos	*next;

	list = *dirList;
	while (list)
	{
		if (list->subDir)
			freeLst(&list->subDir);
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

void	mem_check(void *pointer, t_dirInfos **dirList)
{
	if (pointer == NULL) {
		freeLst(dirList);
		exit(-1);
	}
}