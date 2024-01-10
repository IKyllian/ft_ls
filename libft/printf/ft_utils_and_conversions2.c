/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_and_conversions2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 12:37:48 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:59:51 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	is_flags(char c)
{
	if (c == '0' || c == '-' || c == '*' || c == '.'
		|| (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

void	struct_initialize(t_flags *flags)
{
	flags->has_neg = 0;
	flags->len_field = 0;
	flags->len_is_neg = 0;
	flags->has_dot = 0;
	flags->dot_val = 0;
	flags->has_zero = 0;
	flags->has_star = 0;
	flags->neg_print = 0;
	flags->type = 0;
}

void	check_space_is_neg(t_flags *flags)
{
	if (flags->len_field < 0)
	{
		if (!flags->has_dot)
			flags->has_neg = 1;
		flags->len_field *= -1;
		flags->len_is_neg = 1;
	}
	if (flags->dot_val < 0)
	{
		flags->has_neg = 1;
		flags->dot_val *= -1;
	}
}

void	to_percent(int *count, t_flags *flags)
{
	check_space_is_neg(flags);
	operands_string_dot(*flags, count, 1);
	ope_space_string(*flags, count, 1);
	ft_putchar('%', count);
	ope_space_string_suff(*flags, count, 1);
}

void	to_character(va_list list, int *count, t_flags *flags)
{
	int		nbr;

	check_space_is_neg(flags);
	nbr = va_arg(list, int);
	operands_string_dot(*flags, count, 1);
	ope_space_string(*flags, count, 1);
	ft_putchar(nbr, count);
	ope_space_string_suff(*flags, count, 1);
}
