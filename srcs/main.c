/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:53 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 12:43:51 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	last_exec(t_dirInfos **dir_list, t_datas *datas)
{
	if (*dir_list == NULL)
		return (-1);
	print_list(dir_list, datas, 0);
	free_lst(dir_list);
	return (0);
}

int	ls_exec(t_arg_list **arg_list, t_datas *datas, t_dirInfos **dir_list)
{
	t_arg_list	*list;
	int			last_type;

	list = *arg_list;
	last_type = -1;
	while (list)
	{
		if (last_type != -1 && ((!last_type)
			|| (last_type == 1 && !list->is_file)))
			ft_putchar_fd('\n', 1);
		if (!list->is_file && last_type != -1)
		{
			ft_putstr_fd(list->dir_name, 1);
			ft_putstr_fd(":\n", 1);
		}
		*dir_list = read_dir(datas, list->dir_name, 0, dir_list);
		if (last_exec(dir_list, datas) < 0)
			return (-1);
		last_type = list->is_file;
		list = list->next;
	}
	return (0);
}

int	main(int ac, char **av)
{	
	t_dirInfos	*dir_list;
	t_datas		datas;
	t_arg_list *arg_list;

	dir_list = NULL;
	main_struct_init(&datas);
	arg_list = parser(av, ac, &datas.options);
	if (arg_list == NULL)
		return (-1);
	if (ls_exec(&arg_list, &datas, &dir_list) < 0)
	{
		free_arg_list(&arg_list);
		return (-1);
	}
	free_arg_list(&arg_list);
	return (0);
}
