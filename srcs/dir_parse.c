/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:11:55 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 10:38:26 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirInfos	*fill_variable(t_subDir_infos *sub_dir_infos, \
	struct dirent *current_dir, t_dirInfos **dirList, char **str)
{
	t_dirInfos	*new;

	*str = ft_strjoin(sub_dir_infos->init_path, current_dir->d_name);
	mem_check(*str, dirList);
	new = init_dir_info(current_dir->d_name, *str, sub_dir_infos->is_sub_dir);
	mem_check(new, dirList);
	return (new);
}

int	skip_dir(DIR **p_dir, struct dirent **currt_dir, t_datas *datas)
{
	if (!datas->options.show_hidden && is_hidden_folder((*currt_dir)->d_name))
	{
		(*currt_dir) = readdir(*p_dir);
		return (1);
	}
	return (0);
}

void	loop_end(char **str, struct dirent **currt_dir, DIR **p_dir)
{
	if (*str)
		free(*str);
	*currt_dir = readdir(*p_dir);
}

t_dirInfos	*browse_dir(t_datas *datas, DIR **p_dir, t_dirInfos **dirList, \
	t_subDir_infos *sub_dir_infos)
{
	struct dirent	*currt_dir;
	t_heads_list	heads;
	t_dirInfos		*new;
	char			*str;

	str = NULL;
	heads = init_heads_list(dirList);
	currt_dir = readdir(*p_dir);
	while (currt_dir != NULL)
	{
		if (skip_dir(p_dir, &currt_dir, datas))
			continue ;
		new = fill_variable(sub_dir_infos, currt_dir, dirList, &str);
		heads.ret = ft_lstadd_first(datas->size, &heads, &new, sub_dir_infos);
		if (heads.ret == NULL)
			heads.ret = ft_lstadd_second(&new, &heads, datas->options);
		if (heads.ret == NULL)
			free_mem_dir(&heads.list, &sub_dir_infos->init_path, &str);
		if (datas->options.list_subdir && S_ISDIR(heads.ret->dir_stat.st_mode)
			&& !is_untrack_folder(currt_dir->d_name)
			&& read_dir(datas, str, 1, &heads.ret) == NULL)
			return (free_mem_dir(&heads.list, &sub_dir_infos->init_path, &str));
		loop_end(&str, &currt_dir, p_dir);
	}
	return (heads.list);
}

t_dirInfos	*init_for_file(char *path)
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
	if (dup_strings(&new, path, stat_buffer, path) < 0)
		return (NULL);
	new->dir_stat = stat_buffer;
	new->is_sub_dir = 0;
	new->sub_dir = NULL;
	new->next = NULL;
	new->is_file = 1;
	new->blocks_size = 0;
	return (new);
}

t_dirInfos	*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList)
{
	DIR				*p_dir;
	t_subDir_infos	sub_dir_infos;
	t_dirInfos		*ret;

	errno = 0;
	sub_dir_infos = init_sub_dir_infos(is_sub_dir);
	if (path && path[ft_strlen(path) - 1] == '/')
		sub_dir_infos.init_path = ft_strjoin(path, NULL);
	else
		sub_dir_infos.init_path = ft_strjoin(path, "/");
	mem_check(sub_dir_infos.init_path, dirList);
	p_dir = opendir(path);
	if (p_dir == NULL)
	{
		if (errno == 20)
		{
			if (sub_dir_infos.init_path)
				free(sub_dir_infos.init_path);
			return (init_for_file(path));
		}
		ft_printf("ft_ls: cannot access '%s': No such file or directory\n", \
			path);
		mem_check(p_dir, dirList);
	}
	ret = browse_dir(datas, &p_dir, dirList, &sub_dir_infos);
	if (sub_dir_infos.init_path)
		free(sub_dir_infos.init_path);
	if (p_dir)
		closedir(p_dir);
	return (ret);
}
