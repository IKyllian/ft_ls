/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:15 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/28 10:10:51 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	main_struct_init(t_datas *datas)
{
	datas->options.long_format = 0;
	datas->options.reverse = 0;
	datas->options.show_hidden = 0;
	datas->options.list_subdir = 0;
	datas->options.sort_time = 0;
	datas->error = 0;
	ft_bzero(datas->size, sizeof(datas->size));
}

int	dup_strings(t_dirInfos **new, char dir_name[256], struct stat dir_stat, \
	char *path)
{
	struct group	*group_infos;
	struct passwd	*owner_infos;

	group_infos = getgrgid(dir_stat.st_gid);
	if (!group_infos)
		return (-1);
	owner_infos = getpwuid(dir_stat.st_uid);
	(*new)->dir_name = ft_strdup(dir_name);
	if (!(*new)->dir_name)
		return (-1);
	(*new)->path = ft_strdup(path);
	if (!(*new)->path)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		return (-1);
	}
	(*new)->owner = ft_strdup(owner_infos->pw_name);
	if (!(*new)->owner)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		if ((*new)->path)
			free((*new)->path);
		return (-1);
	}
	(*new)->gr_name = ft_strdup(group_infos->gr_name);
	if (!(*new)->gr_name)
	{
		if ((*new)->dir_name)
			free((*new)->dir_name);
		if ((*new)->path)
			free((*new)->path);
		if ((*new)->owner)
			free((*new)->owner);
		return (-1);
	}
	return (0);
}

t_dirInfos	*init_dir_info(char dir_name[256], char *path, int is_sub_dir)
{
	t_dirInfos	*new;
	struct stat	stat_buffer;

	if (lstat(path, &stat_buffer) < 0)
	{
		ft_printf("Error while Stat\n");
		return (NULL);
	}
	new = (t_dirInfos *)malloc(sizeof(t_dirInfos));
	if (!new)
		return (NULL);
	if (dup_strings(&new, dir_name, stat_buffer, path) < 0)
	{
		if (new)
			free_lst_item(&new);
		return (NULL);
	}
	new->dir_stat = stat_buffer;
	new->is_sub_dir = is_sub_dir;
	new->sub_dir = NULL;
	new->next = NULL;
	new->is_file = 0;
	new->blocks_size = 0;
	return (new);
}

t_subDir_infos	init_sub_dir_infos(int is_sub_dir)
{
	t_subDir_infos	new;

	new.init_path = NULL;
	new.is_first_dir = 1;
	new.is_sub_dir = is_sub_dir;
	return (new);
}

t_heads_list	init_heads_list(t_dirInfos **dirList)
{
	t_heads_list	new;

	new.dir_parent = NULL;
	new.ret = NULL;
	new.list = *dirList;
	return (new);
}
