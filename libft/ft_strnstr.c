/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:37:44 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 10:52:35 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	x;
	char	*str;

	i = 0;
	x = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		if (s1[i] == s2[x])
		{
			str = (char *)&s1[i];
			while (s1[i + x] == s2[x] && i + x < len)
				if (s2[++x] == '\0')
					return (str);
			x = 0;
		}
		i++;
	}
	return (NULL);
}
