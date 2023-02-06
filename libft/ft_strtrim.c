/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:39:00 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 10:54:00 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_start_str(char const *s1, char const *set)
{
	size_t	i;
	int		x;

	i = 0;
	x = 0;
	while (set[x])
	{
		if (set[x] == s1[i])
		{
			x = 0;
			i++;
		}
		else
			x++;
	}
	if (i == ft_strlen(s1))
		return (-1);
	else
		return (i);
}

static	int	check_end_str(char const *s1, char const *set)
{
	int	i;
	int	x;

	i = ft_strlen(s1) - 1;
	x = 0;
	while (set[x])
	{
		if (set[x] == s1[i])
		{
			x = 0;
			i--;
		}
		else
			x++;
	}
	if (i < 0)
		return (-1);
	else
		return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	int		max_len;
	char	*str;

	if (!s1)
		return (NULL);
	i = check_start_str(s1, set);
	max_len = check_end_str(s1, set);
	y = 0;
	str = (char *)malloc(sizeof(*str) * (max_len - i + 2));
	if (!str)
		return (NULL);
	while (s1[i] && i <= max_len && (i != -1 && max_len != -1))
		str[y++] = s1[i++];
	str[y] = '\0';
	return (str);
}
