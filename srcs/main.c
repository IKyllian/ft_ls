/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:53 by kdelport          #+#    #+#             */
/*   Updated: 2024/01/10 11:00:33 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	last_exec(t_dirInfos **dir_list, t_datas *datas)
{
	if (*dir_list == NULL)
		return (-1);
	dir_infos_manager(dir_list, datas, 0);
	free_lst(dir_list);
	return (0);
}

void	print_extra_info(int last_type, t_arg_list *list)
{
	if (last_type != -2 && last_type != -1 && ((!last_type)
			|| (last_type == 1 && !list->is_file)))
		ft_putchar_fd('\n', 1);
	if (!list->is_file && last_type != -1)
	{
		ft_putstr_fd(list->dir_name, 1);
		ft_putstr_fd(":\n", 1);
	}
}

int	ls_exec(t_arg_list **arg_list, t_datas *datas)
{
	t_arg_list	*list;
	int			last_type;
	t_dirInfos	*dir_list;

	list = *arg_list;
	if ((list && list->is_file) || (list && !list->next))
		last_type = -1;
	else
		last_type = -2;
	dir_list = NULL;
	while (list)
	{
		print_extra_info(last_type, list);
		dir_list = read_dir(datas, list->dir_name, 0, &dir_list);
		if (datas->error)
		{
			free_lst(&dir_list);
			return (-1);
		}
		if (last_exec(&dir_list, datas) < 0)
			return (-1);
		last_type = list->is_file;
		list = list->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_datas		datas;
	t_arg_list	*arg_list;

	main_struct_init(&datas);
	arg_list = parser(av, ac, &datas.options);
	if (arg_list == NULL)
		return (-1);
	if (ls_exec(&arg_list, &datas) < 0)
	{
		free_arg_list(&arg_list);
		return (-1);
	}
	free_arg_list(&arg_list);
	return (0);
}
