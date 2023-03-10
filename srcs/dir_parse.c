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
	struct dirent *current_dir, char **str)
{
	t_dirInfos	*new;

	*str = ft_strjoin(sub_dir_infos->init_path, current_dir->d_name);
	if (!*str)
		return (NULL);
	new = init_dir_info(current_dir->d_name, *str, sub_dir_infos->is_sub_dir);
	if (!new)
		return (NULL);
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
	while (currt_dir != NULL)
	{
		if (skip_dir(p_dir, &currt_dir, datas))
			continue ;
		new = fill_variable(sub_dir_infos, currt_dir, &str);
		if (!new)
			return (dir_error(&heads.list, str, datas));
		heads.ret = ft_lstadd_first(datas, &heads, &new, sub_dir_infos);
		if (datas->options.list_subdir && S_ISDIR(heads.ret->dir_stat.st_mode)
			&& !is_untrack_folder(currt_dir->d_name)
			&& read_dir(datas, str, 1, &heads.ret) == NULL)
				return (heads.list);
		loop_end(&str, &currt_dir, p_dir);
	}
	return (heads.list);
}

t_dirInfos	*read_dir(t_datas *datas, char *path, int is_sub_dir, \
	t_dirInfos **dirList)
{
	DIR				*p_dir;
	t_subDir_infos	sub_dir_infos;
	t_dirInfos		*ret;

	errno = 0;
	sub_dir_infos = init_sub_dir_infos(is_sub_dir);
	sub_dir_infos.init_path = join_path(path);
	if (!sub_dir_infos.init_path)
		return (dir_error(dirList, NULL, datas));
	p_dir = opendir(path);
	if (p_dir == NULL)
	{
		if (errno == 20)
			return (create_file(&sub_dir_infos.init_path, path));
		ft_printf("ft_ls: cannot access '%s': No such file or directory\n", \
			path);
		return (dir_error(dirList, sub_dir_infos.init_path, datas));
	}
	ret = browse_dir(datas, &p_dir, dirList, &sub_dir_infos);
	if (sub_dir_infos.init_path)
		free(sub_dir_infos.init_path);
	if (p_dir)
		closedir(p_dir);
	return (ret);
}
