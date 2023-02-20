/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:16:26 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/04 12:01:23 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr(int n, int *count)
{
	long nb;

	nb = n;
	if (nb == -2147483648)
	{
		ft_putstr("2147483648", count);
		return ;
	}
	if (nb < 0)
		nb *= -1;
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, count);
		ft_putnbr(nb % 10, count);
	}
	else
		ft_putchar(nb + 48, count);
}

void	ft_unsigned_putnbr(unsigned long long n, int *count)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
	else
		ft_putchar(n + 48, count);
}
