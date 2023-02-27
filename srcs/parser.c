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

int	parser(char **av, t_options *options)
{
	int	i;
	int	j;
	int	is_flag;

	i = 1;
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
					return (-2);
			}
			else
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
