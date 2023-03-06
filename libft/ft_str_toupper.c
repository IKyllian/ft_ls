/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:50:52 by kdelport          #+#    #+#             */
/*   Updated: 2023/03/06 11:24:40 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_toupper(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	while (str[i])
	{
		new[i] = ft_toupper(str[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
