/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operands_string_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:08:17 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/04 10:01:17 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	operands_string_dot(t_flags flags, int *count, int len)
{
	if (flags.dot_val && !flags.has_neg)
	{
		if (flags.has_zero && !flags.has_neg)
		{
			if (flags.len_field < len && !flags.len_is_neg && flags.type == 's')
				fill_space('0', (flags.dot_val - flags.len_field), count);
			else
				fill_space('0', (flags.dot_val - len), count);
		}
		else if (!flags.has_neg)
		{
			if (flags.len_field < len && !flags.len_is_neg && flags.type == 's')
				fill_space(' ', (flags.dot_val - flags.len_field), count);
			else
				fill_space(' ', (flags.dot_val - len), count);
		}
	}
}

void	ope_space_string(t_flags flags, int *count, int len)
{
	if (flags.len_field && !flags.has_neg && !flags.has_dot)
	{
		if (flags.has_zero)
			fill_space('0', (flags.len_field - len), count);
		else
			fill_space(' ', (flags.len_field - len), count);
	}
}

void	ope_space_string_suff(t_flags flags, int *count, int len)
{
	if (flags.has_neg && !flags.has_dot)
		fill_space(' ', (flags.len_field - len), count);
	else if (flags.has_dot && flags.len_is_neg && !flags.has_star)
	{
		if (flags.type == 'c' || flags.type == '%')
			fill_space(' ', (flags.len_field - len), count);
		else
			fill_space(' ', flags.len_field, count);
	}
	else if (flags.has_neg && flags.dot_val)
	{
		if (flags.len_is_neg || flags.len_field >= len ||
			(!flags.len_field && (flags.type == 'c' || flags.type == '%')))
			fill_space(' ', (flags.dot_val - len), count);
		else
		{
			fill_space(' ', (flags.dot_val - flags.len_field), count);
		}
	}
}

void	print_string(t_flags flags, int *count, char *str, int len)
{
	int i;
	int size;

	i = 0;
	size = 0;
	if (flags.has_dot)
	{
		if (flags.len_field)
		{
			if (flags.len_is_neg && flags.has_star)
				size = len;
			else if (flags.len_is_neg && !flags.has_star)
				size = 0;
			else
				size = flags.len_field;
		}
		if (size > len)
			size = len;
		while (str && size--)
			ft_putchar(str[i++], count);
	}
	else
		ft_putstr(str, count);
}
