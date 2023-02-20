/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:07:45 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/05 13:17:00 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		u_nbr_len(unsigned long long nbr, unsigned int size_base)
{
	int			length;

	length = 0;
	while (nbr >= size_base)
	{
		length++;
		nbr /= size_base;
	}
	return (++length);
}

int		ft_itoh(unsigned long long nb, int low, int *ct, t_flags *flg)
{
	char	*str;
	int		i;
	char	*base;

	i = u_nbr_len(nb, 16);
	if (low)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (!(str = malloc(sizeof(char) * (u_nbr_len(nb, 16) + 1))))
		return (1);
	str[i--] = 0;
	if (nb == 0 && flg->len_is_neg && !flg->has_star)
		str[i--] = ' ';
	else if (nb == 0)
		str[i--] = '0';
	while (nb)
	{
		str[i--] = base[nb % 16];
		nb /= 16;
	}
	ft_putstr(str, ct);
	free(str);
	return (0);
}
