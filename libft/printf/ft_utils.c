/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:18:53 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:59:26 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_count_numbers(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] && ((*str)[i] >= 48 && (*str)[i] <= 57))
		i++;
	if (*(*str - 1) == '-' && *(*str - 2) == '.')
		i++;
	return (i);
}

int	ft_convert(char **str, va_list list, int *count, t_flags *flag)
{
	if (*(*str) == 's')
		to_string(list, count, *flag);
	else if (*(*str) == 'd' || *(*str) == 'i')
		to_decimal(list, count, flag);
	else if (*(*str) == 'u')
		to_unsigned_decimal(list, count, flag);
	else if (*(*str) == 'x')
	{
		if (to_hexa(list, count, 1, flag) == 1)
			return (1);
	}
	else if (*(*str) == 'X')
		to_hexa(list, count, 0, flag);
	else if (*(*str) == 'c')
		to_character(list, count, flag);
	else if (*(*str) == '%')
		to_percent(count, flag);
	else if (*(*str) == 'p')
	{
		if (to_pointer_address(list, count, flag) == 1)
			return (1);
	}
	else
		ft_putchar(*(*str), count);
	return (0);
}
