/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:46 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:40:56 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirInfos	*change_head_list(t_dirInfos **new, t_dirInfos *list, \
	t_heads_list *heads_list)
{
	(*new)->blocks_size = list->blocks_size;
	(*new)->blocks_size += (*new)->dir_stat.st_blocks;
	if (heads_list->dir_parent)
		heads_list->dir_parent->sub_dir = *new;
	heads_list->list = *new;
	return (*new);
}

t_dirInfos	*ft_lstadd_first(int size[SIZE_LENGTH], t_heads_list *heads_list, \
	t_dirInfos **new, t_subDir_infos *subDirInfos)
{
	set_column_size(size, *new);
	if (heads_list->list == NULL)
	{
		(*new)->blocks_size += (*new)->dir_stat.st_blocks;
		heads_list->list = *new;
		subDirInfos->is_first_dir = 0;
		return (heads_list->list);
	}
	else if (subDirInfos->is_first_dir)
	{
		(*new)->blocks_size += (*new)->dir_stat.st_blocks;
		heads_list->list->sub_dir = *new;
		if (subDirInfos->is_sub_dir)
		{
			heads_list->dir_parent = heads_list->list;
			heads_list->list = *new;
		}
		subDirInfos->is_first_dir = 0;
		return (*new);
	}
	return (NULL);
}

t_dirInfos	*ft_lstadd_second(t_dirInfos **new, t_heads_list *heads_list, \
	t_options	options)
{
	t_dirInfos	*list;
	t_dirInfos	*last;

	last = NULL;
	list = heads_list->list;
	while (list)
	{
		if ((sort_by_time(*new, list, options)) || (!options.sort_time
				&& sort_by_letter(*new, list, options.reverse)))
		{
			(*new)->next = list;
			if (last != NULL)
				last->next = *new;
			else
				return (change_head_list(new, list, heads_list));
			heads_list->list->blocks_size += (*new)->dir_stat.st_blocks;
			return (*new);
		}
		last = list;
		list = list->next;
	}
	last->next = *new;
	heads_list->list->blocks_size += (*new)->dir_stat.st_blocks;
	return (*new);
}
