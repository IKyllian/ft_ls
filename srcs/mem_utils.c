/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:00 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 12:59:37 by kdelport         ###   ########.fr       */
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
		if (list->path)
			free(list->path);
		if (list->dir_name)
			free(list->dir_name);
		if (list->owner)
			free(list->owner);
		if (list->gr_name)
			free(list->gr_name);
		next = list->next;
		free(list);
		list = next;
	}
	*dirList = NULL;
}

void	mem_check(void *pointer, t_dirInfos **dirList)
{
	if (pointer == NULL)
	{
		free_lst(dirList);
		exit(-1);
	}
}

void	*free_mem_dir(t_dirInfos **list, char **init_path, char **path)
{
	if (*init_path)
		free(*init_path);
	*init_path = NULL;
	if (*path)
		free(*path);
	free_lst(list);
	return (NULL);
}

void	free_array(char ***arg_list)
{
	int	i;

	i = 0;
	while ((*arg_list)[i])
	{
		free((*arg_list)[i]);
		i++;
	}
	free(*arg_list);
}
