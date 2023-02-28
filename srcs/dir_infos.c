/* ************************************************************************** */
/*	                                                                    */
/*                                                        :::      ::::::::   */
/*   dir_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:39 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 10:51:19 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_permision(struct stat dir_stat, char str[SIZE_PERM])
{
	str[0] = set_file_type(dir_stat.st_mode);
	if (dir_stat.st_mode & S_IRUSR)
		str[1] = 'r';
	if (dir_stat.st_mode & S_IWUSR)
		str[2] = 'w';
	if (dir_stat.st_mode & S_IXUSR)
		str[3] = 'x';
	if (dir_stat.st_mode & S_IRGRP)
		str[4] = 'r';
	if (dir_stat.st_mode & S_IWGRP)
		str[5] = 'w';
	if (dir_stat.st_mode & S_IXGRP)
		str[6] = 'x';
	if (dir_stat.st_mode & S_IROTH)
		str[7] = 'r';
	if (dir_stat.st_mode & S_IWOTH)
		str[8] = 'w';
	if (dir_stat.st_mode & S_IXOTH)
		str[9] = 'x';
}

char	set_file_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

void	set_column_size(int size[SIZE_LENGTH], t_dirInfos *dir)
{
	size[0] = max_nbr(integer_length(dir->dir_stat.st_nlink), size[0]);
	size[1] = max_nbr(ft_strlen(dir->owner), size[1]);
	size[2] = max_nbr(ft_strlen(dir->gr_name), size[2]);
	size[3] = max_nbr(integer_length(dir->dir_stat.st_size), size[3]);
}
