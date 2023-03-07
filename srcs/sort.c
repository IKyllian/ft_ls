/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:33:52 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 11:23:49 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_by_letter(t_dirInfos *new, t_dirInfos *list, int reverse)
{
	char	*new_name;
	char	*list_name;
	int		ret;

	new_name = ft_str_tolower(new->dir_name);
	list_name = ft_str_tolower(list->dir_name);
	ret = ((!reverse && new->is_file && strcmp(new_name, list_name) < 0)
			|| (reverse && strcmp(new_name, list_name) > 0));
	free(new_name);
	free(list_name);
	return (ret);
}

int	sort_by_time(t_dirInfos *new, t_dirInfos *list, t_options	options)
{
	if (options.sort_time && new->dir_stat.st_mtime == list->dir_stat.st_mtime)
	{
		if (options.sort_time && new->dir_stat.st_mtimespec.tv_nsec \
			== list->dir_stat.st_mtimespec.tv_nsec)
			return (sort_by_letter(new, list, options.reverse));
		else
			return ((options.sort_time && !options.reverse
					&& new->dir_stat.st_mtimespec.tv_nsec \
					> list->dir_stat.st_mtimespec.tv_nsec)
				|| (options.sort_time && options.reverse
					&& new->dir_stat.st_mtimespec.tv_nsec \
					< list->dir_stat.st_mtimespec.tv_nsec));
	}
	return ((options.sort_time && !options.reverse
			&& new->dir_stat.st_mtime > list->dir_stat.st_mtime)
		|| (options.sort_time && options.reverse
			&& new->dir_stat.st_mtime < list->dir_stat.st_mtime));
}
