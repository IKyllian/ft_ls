/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:10 by kdelport          #+#    #+#             */
/*   Updated: 2024/01/11 11:06:43 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir_name(char *name, mode_t mode)
{
	if (S_ISDIR(mode))
		ft_printf("%s%s%s", COLOR_CYAN, name, COLOR_DEFAULT);
	else if (S_ISLNK(mode))
		ft_printf("%s%s%s", COLOR_PURPLE, name, COLOR_DEFAULT);
	else if (mode & S_IXUSR)
		ft_printf("%s%s%s", COLOR_GREEN, name, COLOR_DEFAULT);
	else
		ft_printf("%s", name);
}

void	print_items(t_dirInfos *dir, int size[SIZE_LENGTH], char *dir_time, \
	char permisions[SIZE_PERM])
{
	char	buff[NAME_MAX + 1];

	ft_printf("%s ", permisions);
	ft_printf("%*i ", size[0], dir->dir_stat.st_nlink);
	ft_printf("%-*s ", size[1], dir->owner);
	ft_printf(" %-*s ", size[2], dir->gr_name);
	ft_printf(" %*i ", size[3], dir->dir_stat.st_size);
	print_date(dir, dir_time);
	if (permisions[0] == 'l')
	{
		ft_bzero(buff, NAME_MAX + 1);
		readlink(dir->path, buff, NAME_MAX + 1);
		ft_printf("%s%s%s -> %s", COLOR_PURPLE, dir->dir_name, \
			COLOR_DEFAULT, buff);
	}
	else
		print_dir_name(dir->dir_name, dir->dir_stat.st_mode);
}

void	exec_long_format(t_dirInfos *dir, int size[SIZE_LENGTH])
{
	char	permisions[SIZE_PERM];
	char	*dir_time;
	int		i;

	i = 0;
	while (i < SIZE_PERM - 2)
		permisions[i++] = '-';
	permisions[i++] = get_file_attributes(dir);
	permisions[i] = '\0';
	set_permision(dir->dir_stat, permisions);
	dir_time = ctime(&dir->dir_stat.st_mtime) + 4;
	print_items(dir, size, dir_time, permisions);
}

void	print_dir_infos(int is_sub, t_dirInfos **list, t_dirInfos	**head, \
	t_datas *datas)
{
	if (is_sub)
	{
		ft_printf("\n%s:\n", (*list)->path);
		(*list) = (*list)->sub_dir;
		(*head) = (*head)->sub_dir;
	}
	if (datas->options.long_format && (*list) && !(*list)->is_file)
		ft_printf("total %i\n", (*list)->blocks_size / 2);
}

void	dir_infos_manager(t_dirInfos **dirList, t_datas *datas, int is_sub)
{
	t_dirInfos	*list;
	t_dirInfos	*head;

	list = *dirList;
	head = *dirList;
	print_dir_infos(is_sub, &list, &head, datas);
	while (list)
	{
		if (datas->options.long_format)
			exec_long_format(list, datas->size);
		else
			print_dir_name(list->dir_name, list->dir_stat.st_mode);
		ft_putchar_fd('\n', 1);
		list = list->next;
	}
	while (head)
	{
		if (head->sub_dir)
			dir_infos_manager(&head, datas, 1);
		head = head->next;
	}
}
