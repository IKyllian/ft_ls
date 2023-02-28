/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:10 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/28 12:41:12 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_long_format(t_dirInfos *dir, int size[SIZE_LENGTH])
{
	char	permisions[SIZE_PERM];
	char	*dir_time;
	int		i;

	i = 0;
	while (i < 10)
	{
		permisions[i] = '-';
		i++;
	}
	permisions[i] = '\0';
	set_permision(dir->dir_stat, permisions);
	dir_time = ctime(&dir->dir_stat.st_mtime) + 4;
	ft_printf("%s ", permisions);
	ft_printf("%*i ", size[0], dir->dir_stat.st_nlink);
	ft_printf("%-*s ", size[1], dir->owner);
	ft_printf(" %-*s ", size[2], dir->gr_name);
	ft_printf(" %*i ", size[3], dir->dir_stat.st_size);
	ft_printf("%.12s ", dir_time);
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
	if (datas->options.long_format && (*list))
		ft_printf("total %i\n", (*list)->blocks_size / 2);
}

void	print_list(t_dirInfos **dirList, t_datas *datas, int is_sub)
{
	t_dirInfos	*list;
	t_dirInfos	*head;

	list = *dirList;
	head = *dirList;
	print_dir_infos(is_sub, &list, &head, datas);
	while (list)
	{
		if (datas->options.long_format)
			print_long_format(list, datas->size);
		ft_printf("%s \n", list->dir_name);
		list = list->next;
	}
	while (head)
	{
		if (head->sub_dir)
			print_list(&head, datas, 1);
		head = head->next;
	}
}
