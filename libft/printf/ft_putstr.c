/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:15:33 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 14:04:23 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++], count);
}

void	fill_space(char c, int size, int *count)
{
	int	i;

	i = 0;
	while (i++ < size)
		ft_putchar(c, count);
}
