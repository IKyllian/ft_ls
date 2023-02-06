/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:01:04 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 10:59:02 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*free_tab(char **str, int length)
{
	while (length--)
		free(*str++);
	free(str);
	return (NULL);
}

static	int	get_strings_len(char const *str, char sep)
{
	int	compt;

	compt = 0;
	while (*str)
	{
		if (*str == sep)
			return (compt);
		str++;
		compt++;
	}
	return (compt);
}

static	int	get_tab_len(char const *str, char sep)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (str[0] == sep)
		x = -1;
	while (str[i])
	{
		while (str[i] && str[i] != sep)
			i++;
		x++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (x);
}

static	char	**fill_tab(char const *str, char **output, char sep)
{
	int	i;
	int	x;

	x = 0;
	while (*str)
	{
		if (*str != sep)
		{
			output[x] = malloc(sizeof(**output) * \
				(get_strings_len(str, sep) + 1));
			if (!output[x])
				return (free_tab(output, x));
			i = 0;
			while (*str != sep && *str)
				output[x][i++] = *str++;
			output[x++][i] = '\0';
		}
		else
			str++;
	}
	output[x] = 0;
	return (output);
}

char	**ft_split(char const *s, char c)
{
	int		length;
	char	**output;

	if (!s)
		return (NULL);
	length = get_tab_len(s, c);
	output = malloc(sizeof(*output) * (length + 1));
	if (!output)
		return (NULL);
	if (length)
		return (fill_tab(s, output, c));
	output[0] = 0;
	return (output);
}
