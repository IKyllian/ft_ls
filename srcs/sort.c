/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:33:52 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 12:47:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_by_letter(t_dirInfos *new, t_dirInfos *list, int reverse)
{
	return ((!reverse && strcmp(new->dir_name, list->dir_name) < 0)
		|| (reverse && strcmp(new->dir_name, list->dir_name) > 0));
}

int	sort_by_time(t_dirInfos *new, t_dirInfos *list, t_options	options)
{
	if (new->dir_stat.st_mtime == list->dir_stat.st_mtime)
	{
		// if (new->dir_stat.st_atime == list->dir_stat.st_atime) {
		//   if (new->dir_stat.st_ctime == list->dir_stat.st_ctime)
				return (sort_by_letter(new, list, !options.reverse));
		//  else
		//   return ((options.sort_time && !options.reverse && new->dir_stat.st_ctime > list->dir_stat.st_ctime)
		//	 || (options.sort_time && options.reverse && new->dir_stat.st_ctime < list->dir_stat.st_ctime));
		// } else
		//   return ((options.sort_time && !options.reverse && new->dir_stat.st_atime > list->dir_stat.st_atime)
		//	 || (options.sort_time && options.reverse && new->dir_stat.st_atime < list->dir_stat.st_atime));
	}   
	return ((options.sort_time && !options.reverse && new->dir_stat.st_mtime > list->dir_stat.st_mtime)
		|| (options.sort_time && options.reverse && new->dir_stat.st_mtime < list->dir_stat.st_mtime));
}
