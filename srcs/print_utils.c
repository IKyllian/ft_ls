/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:52:36 by kdelport          #+#    #+#             */
/*   Updated: 2024/01/11 11:10:19 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_file_attributes(t_dirInfos *dir)
{
	char	buff2[101];

	if (listxattr(dir->path, buff2, sizeof(buff2)) > 0)
		return ('@');
	return (' ');
}

void	print_date(t_dirInfos *dir, char *dir_time)
{
	time_t	now;
	time_t	six_months_seconds;
	time_t	future_time;

	now = time(NULL);
	six_months_seconds = 6 * 30 * 24 * 60 * 60;
	future_time = dir->dir_stat.st_mtime + six_months_seconds;
	if (now > future_time)
		ft_printf("%.7s %.4s ", dir_time, &(dir_time[strlen(dir_time) - 5]));
	else
		ft_printf("%.12s ", dir_time);
}
