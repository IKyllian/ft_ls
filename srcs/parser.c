/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:06 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 12:14:10 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	flag_check(char c, t_options *options)
{
	if (!char_is_flag(c))
	{
		ft_printf("ft_ls : invalid option -- %c\n", c);
		ft_printf("usage: ls [-Ralrt] [file ...] \n");
		return (-1);
	}
	fill_options(c, options);
	return (0);
}

int	check_dir_exist(char *path)
{
	DIR	*p_dir;

	p_dir = opendir(path);
	if (p_dir == NULL)
	{
		ft_printf("ft_ls: cannot access '%s': No such file or directory\n", path);
		return (-1);
	}
	closedir(p_dir);
	return (0);
}

char	**parser(char **av, int ac, t_options *options)
{
	int	i;
	int	j;
	int	idx;
	int	is_flag;
	char	**arg_list;

	i = 1;
	idx = 0;
	arg_list = (char **)malloc(sizeof(char *) * ac);
	if (!arg_list)
		return (NULL);
	while (av[i])
	{
		is_flag = 0;
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '-')
				is_flag = 1;
			else if (is_flag)
			{
				if (flag_check(av[i][j], options) < 0)
				{
					free_array(&arg_list);
					return (NULL);
				}
			}
			else
			{
				if (check_dir_exist(av[i]) != -1)
					arg_list[idx++] = ft_strdup(av[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	arg_list[idx] = NULL;
	return (arg_list);
}
