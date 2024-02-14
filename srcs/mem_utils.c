/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:00 by kdelport          #+#    #+#             */
/*   Updated: 2024/02/14 13:24:28 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_lst(t_dirInfos **dirList)
{
	t_dirInfos	*list;
	t_dirInfos	*next;

	list = *dirList;
	while (list)
	{
		if (list->sub_dir)
			free_lst(&list->sub_dir);
		next = list->next;
		free_lst_item(&list);
		list = next;
	}
	*dirList = NULL;
}

void	free_lst_item(t_dirInfos **item)
{
	if ((*item)->path)
		free((*item)->path);
	if ((*item)->dir_name)
		free((*item)->dir_name);
	if ((*item)->owner)
		free((*item)->owner);
	if ((*item)->gr_name)
		free((*item)->gr_name);
	free((*item));
	*item = NULL;
}

void	free_arg_list(t_arg_list **arg_list)
{
	t_arg_list	*list;
	t_arg_list	*next;

	list = *arg_list;
	while (list)
	{
		if (list->dir_name)
			free(list->dir_name);
		next = list->next;
		free(list);
		list = next;
	}
	*arg_list = NULL;
}

t_dirInfos	*dir_error(t_dirInfos **head, char *ptr, t_datas *datas)
{
	if (ptr)
		free(ptr);
	(void)ptr;
	datas->error = 1;
	return (*head);
}
