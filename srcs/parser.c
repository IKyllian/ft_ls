/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:06 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 12:42:39 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	flag_check(char c, t_options *options, char ***arg_list)
{
	if (!char_is_flag(c))
	{
		ft_printf("ft_ls : invalid option -- %c\n", c);
		ft_printf("usage: ls [-Ralrt] [file ...] \n");
		free_array(arg_list);
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
		ft_printf("ft_ls: cannot access '%s': No such file or directory\n", \
			path);
		return (-1);
	}
	closedir(p_dir);
	return (0);
}

int	arg_check(char *av, t_options *options, char ***arg_list, int *idx)
{
	int	j;
	int	is_flag;

	is_flag = 0;
	j = -1;
	while (av[++j])
	{
		if (j == 0 && av[j] == '-')
			is_flag = 1;
		else if (is_flag)
		{
			if (flag_check(av[j], options, arg_list) < 0)
				return (-1);
		}
		else
		{
			if (check_dir_exist(av) != -1)
				(*arg_list)[*idx++] = ft_strdup(av);
			break ;
		}
	}
	return (0);
}

int	parse_exec(char **av, t_options *options, char ***arg_list)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (av[++i])
	{
		if (arg_check(av[i], options, arg_list, &idx) < 0)
			return (-1);
	}
	(*arg_list)[idx] = NULL;
	return (0);
}

char	**parser(char **av, int ac, t_options *options)
{
	char	**arg_list;

	arg_list = (char **)malloc(sizeof(char *) * ac);
	if (!arg_list)
		return (NULL);
	if (parse_exec(av, options, &arg_list) < 0)
		return (NULL);
	return (arg_list);
}
