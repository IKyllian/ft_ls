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

int	ls_exec(char **arg_list, t_datas *datas, t_dirInfos **dir_list)
{
	int	i;
	int	length;

	i = -1;
	length = array_length(arg_list);
	if (arg_list[0] == NULL)
		*dir_list = read_dir(datas, ".", 0, dir_list);
	else
	{
		while (arg_list[++i])
		{
			if (i != 0)
				ft_putchar_fd('\n', 1);
			if (length > 1)
			{
				ft_putstr_fd(arg_list[i], 1);
				ft_putstr_fd(":\n", 1);
			}
			*dir_list = read_dir(datas, arg_list[i], 0, dir_list);
			if (last_exec(dir_list, datas) < 0)
				return (-1);
		}
		return (0);
	}
	return (last_exec(dir_list, datas));
}

int	main(int ac, char **av)
{	
	t_dirInfos	*dir_list;
	t_datas		datas;
	char		**arg_list;

	dir_list = NULL;
	main_struct_init(&datas);
	arg_list = parser(av, ac, &datas.options);
	if (arg_list == NULL)
		return (-1);
	if (ls_exec(arg_list, &datas, &dir_list) < 0)
	{
		free_array(&arg_list);
		return (-1);
	}
	free_array(&arg_list);
	return (0);
}
