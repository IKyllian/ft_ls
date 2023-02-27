/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:53 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:44:57 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_heads_list	init_heads_list(t_dirInfos **dirList)
{
	t_heads_list	new;

	new.dir_parent = NULL;
	new.ret = NULL;
	new.list = *dirList;
	return (new);
}

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
	while (currt_dir)
	{
		if (!datas->options.show_hidden && is_hidden_folder(currt_dir->d_name))
			continue ;
		fill_variable(sub_dir_infos, currt_dir, dirList, &str);
		heads.ret = ft_lstadd_first(datas->size, &heads, &new, sub_dir_infos);
		if (heads.ret == NULL)
			heads.ret = ft_lstadd_second(&new, &heads, datas->options);
		if (datas->options.list_subdir && S_ISDIR(heads.ret->dir_stat.st_mode)
			&& !is_untrack_folder(currt_dir->d_name)
			&& read_dir(datas, str, 1, &heads.ret) == NULL)
			return (free_mem_dir(&heads.list, &sub_dir_infos->init_path, &str));
		if (str)
			free(str);
		currt_dir = readdir(*p_dir);
	}
	return (heads.list);
}

t_dirInfos	*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList)
{
	DIR				*p_dir;
	t_subDir_infos	sub_dir_infos;
	t_dirInfos		*ret;

	sub_dir_infos = init_sub_dir_infos(is_sub_dir);
	if (path && path[ft_strlen(path) - 1] == '/')
		sub_dir_infos.init_path = ft_strjoin(path, NULL);
	else
		sub_dir_infos.init_path = ft_strjoin(path, "/");
	mem_check(sub_dir_infos.init_path, dirList);
	p_dir = opendir(path);
	mem_check(p_dir, dirList);
	ret = browse_dir(datas, &p_dir, dirList, &sub_dir_infos);
	if (sub_dir_infos.init_path)
		free(sub_dir_infos.init_path);
	closedir(p_dir);
	return (ret);
}

int	main(int ac, char **av)
{	
	int			path_index;
	t_dirInfos	*dir_list;
	t_datas		datas;

	dir_list = NULL;
	path_index = -1;
	main_struct_init(&datas);
	if (ac > 1)
		path_index = parser(av, &datas.options);
	if (path_index == -2)
		return (-1);
	if (path_index > 0)
		dir_list = read_dir(&datas, av[path_index], 0, &dir_list);
	else
		dir_list = read_dir(&datas, ".", 0, &dir_list);
	if (dir_list == NULL)
		return (-1);
	print_list(&dir_list, &datas, 0);
	free_lst(&dir_list);
	return (0);
}
