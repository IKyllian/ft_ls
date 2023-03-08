/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:06 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 13:06:36 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	flag_check(char c, t_options *options, t_arg_list **arg_list)
{
	if (!char_is_flag(c))
	{
		ft_printf("ft_ls : invalid option -- %c\n", c);
		ft_printf("usage: ls [-Ralrt] [file ...] \n");
		free_arg_list(arg_list);
		return (-1);
	}
	fill_options(c, options);
	return (0);
}

int	check_dir_exist(char *path) // 1 = file | 0 = folder
{
	DIR	*p_dir;
	errno = 0;

	p_dir = opendir(path);
	if (p_dir == NULL)
	{
		if (errno == 20)
			return (1);
		ft_printf("ft_ls: cannot access '%s': No such file or directory\n", \
			path);
		return (-1);
	}
	if (p_dir)
		closedir(p_dir);
	return (0);
}

int	search_options(char **av, t_options *options, t_arg_list **arg_list)
{
	int	i;
	int	j;
	int	is_flag;
	int	count;

	i = 0;
	count = 0;
	while (av[++i])
	{
		is_flag = 0;
		j = -1;
		while (av[i][++j])
		{
			if (ft_strlen(av[i]) > 1 && j == 0 && av[i][j] == '-')
			{
				is_flag = 1;
				count++;
			}
			else if (is_flag)
			{
				if (flag_check(av[i][j], options, arg_list) < 0)
					return (-1);
				
			}
			else
				break;
		}
	}
	return (count);
}

int	parse_exec(char **av, t_options *options, t_arg_list **arg_list)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (av[++i])
	{
		if (ft_strlen(av[i]) > 1 && av[i][0] == '-')
			continue;
		ret = check_dir_exist(av[i]);
		if (ret != -1)
			*arg_list = add_arg(av[i], ret, arg_list, *options);
	}
	return (0);
}

t_arg_list	*parser(char **av, int ac, t_options *options)
{
	t_arg_list	*arg_list;
	int			ret;

	arg_list = NULL;
	ret = search_options(av, options, &arg_list);
	if (ret < 0)
		return (NULL);
	if (ret == (ac - 1))
	{
		ret = check_dir_exist(".");
		if (ret != -1)
			arg_list = add_arg(".", ret, &arg_list, *options);
	}
	else
		parse_exec(av, options, &arg_list);
	return (arg_list);
}
