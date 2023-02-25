#include "ft_ls.h"

t_dirInfos	*change_head_list(t_dirInfos **new, t_dirInfos *list, t_heads_list *heads_list)
{
	(*new)->blocksSize = list->blocksSize;
	(*new)->blocksSize += (*new)->dirStat.st_blocks;
	if (heads_list->dirParent)
		heads_list->dirParent->subDir = *new;
	heads_list->list = *new;
	return (*new);
}

t_dirInfos	*ft_lstadd_first(int size[SIZE_LENGTH], t_heads_list *heads_list, t_dirInfos **new, t_subDir_infos *subDirInfos)
{
	setColumnSize(size, *new);
	if (heads_list->list == NULL)
	{
		(*new)->blocksSize += (*new)->dirStat.st_blocks;
		heads_list->list = *new;
		subDirInfos->isFirstDir = 0;
		return (heads_list->list);
	 } else if (subDirInfos->isFirstDir)
	 {
		(*new)->blocksSize += (*new)->dirStat.st_blocks;
		heads_list->list->subDir = *new;
		if (subDirInfos->isSubDir)
		{
			heads_list->dirParent = heads_list->list;
			heads_list->list = *new;
		}
		subDirInfos->isFirstDir = 0;
		return (*new);
	}
	return (NULL);
}

t_dirInfos	*ft_lstadd_second(t_dirInfos **new, t_heads_list *heads_list, int isReverse)
{
	t_dirInfos *list;
	t_dirInfos *last;

	last = NULL;
	list = heads_list->list;
	while (list)
	{
		if ((!isReverse && strcmp((*new)->dirName, list->dirName) < 0) || (isReverse && strcmp((*new)->dirName, list->dirName) > 0))
		{
			(*new)->next = list;
			if (last != NULL)
				last->next = *new;
			else
				return (change_head_list(new, list, heads_list));
			heads_list->list->blocksSize += (*new)->dirStat.st_blocks;
			return (*new);
		}
		last = list;
		list = list->next;
	}
	last->next = *new;
	heads_list->list->blocksSize += (*new)->dirStat.st_blocks;
	return (*new);
}