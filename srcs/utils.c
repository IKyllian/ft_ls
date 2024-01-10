/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:35:22 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/28 10:31:55 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	char_is_flag(char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (1);
	return (0);
}

void	fill_options(char c, t_options *options)
{
	if (c == 'r')
		options->reverse = 1;
	else if (c == 'a')
		options->show_hidden = 1;
	else if (c == 'l')
		options->long_format = 1;
	else if (c == 'R')
		options->list_subdir = 1;
	else if (c == 't')
		options->sort_time = 1;
}

int	is_untrack_folder(char *str)
{
	if (ft_strlen(str) == 1 && str[0] == '.')
		return (1);
	else if (ft_strlen(str) == 2 && str[0] == '.' && str[1] == '.')
		return (1);
	return (0);
}

int	is_hidden_folder(char *str)
{
	if (ft_strlen(str) > 0 && str[0] == '.')
		return (1);
	return (0);
}

int	max_nbr(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
