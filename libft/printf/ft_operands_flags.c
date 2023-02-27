/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operands_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:08:29 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:51:30 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_neg(int arg, int *count, t_flags *flags, int *arg_len)
{
	if (arg < 0 && !flags->neg_print
		&& (flags->type == 'i' || flags->type == 'd'))
	{
		ft_putchar('-', count);
		flags->neg_print = 1;
	}
	else if (!flags->neg_print && flags->type == 'p')
	{
		ft_putstr("0x", count);
		flags->neg_print = 1;
		if (flags->has_dot && flags->len_field > (*arg_len - 2)
			&& !flags->len_is_neg)
			*arg_len -= 2;
	}
}

void	ope_dot_address(t_flags *f, int *count, int arg, int *len)
{
	if (f->has_dot && (!f->has_neg || (!f->has_neg && f->len_is_neg)))
	{
		if (f->dot_val >= f->len_field && !f->len_is_neg)
		{
			if (f->len_field >= *len)
			{
				if ((f->dot_val - f->len_field) > 0)
					fill_space(' ', (f->dot_val - f->len_field - 2), count);
			}
			else if (f->dot_val - *len > 0 && (*len - f->len_field == 1))
				fill_space(' ', (f->dot_val - *len - 1), count);
			else if (f->dot_val - *len > 0)
				fill_space(' ', (f->dot_val - *len), count);
		}
		else if (f->len_is_neg && (f->dot_val - *len > 0)
			&& !f->has_zero)
			fill_space(' ', (f->dot_val - *len), count);
		else if (f->len_is_neg && (f->dot_val - *len > 0)
			&& f->has_zero)
		{
			print_neg(arg, count, f, len);
			fill_space('0', (f->dot_val - *len), count);
		}
		print_neg(arg, count, f, len);
	}
}

void	ope_dot(t_flags *f, int *count, int arg, int *len)
{
	if (f->has_dot && (!f->has_neg || (!f->has_neg && f->len_is_neg)))
	{
		if (arg < 0 && (f->type == 'd' || f->type == 'i'))
			f->dot_val -= 1;
		if (f->dot_val >= f->len_field && !f->len_is_neg)
		{
			if (f->len_field >= *len)
			{
				if ((f->dot_val - f->len_field) > 0)
					fill_space(' ', (f->dot_val - f->len_field), count);
			}
			else if (f->dot_val - *len > 0)
				fill_space(' ', (f->dot_val - *len), count);
		}
		else if (f->len_is_neg && (f->dot_val - *len > 0)
			&& !f->has_zero)
			fill_space(' ', (f->dot_val - *len), count);
		else if (f->len_is_neg && (f->dot_val - *len > 0)
			&& f->has_zero)
		{
			print_neg(arg, count, f, len);
			fill_space('0', (f->dot_val - *len), count);
		}
		print_neg(arg, count, f, len);
	}
}

void	ope_space(t_flags *flags, int *count, int arg, int *len)
{
	if ((flags->len_field && !flags->has_neg && flags->len_field > *len
			&& !flags->len_is_neg) || (flags->len_field && flags->has_neg
			&& flags->has_dot && !flags->len_is_neg))
	{
		if (arg < 0 && !flags->has_dot)
			flags->len_field -= 1;
		if ((flags->has_zero && !flags->has_neg && !flags->len_is_neg)
			|| (flags->has_dot && !flags->len_is_neg))
		{
			print_neg(arg, count, flags, len);
			fill_space('0', (flags->len_field - *len), count);
		}
		else if (!flags->has_neg)
			fill_space(' ', (flags->len_field - *len), count);
		if (arg < 0 && !flags->has_zero && !flags->neg_print)
			print_neg(arg, count, flags, len);
	}
	else if (arg < 0 && !(flags->neg_print))
		print_neg(arg, count, flags, len);
}

void	ope_space_suff(t_flags *flags, int *count, int arg, int len)
{
	if (arg < 0 && !(flags->has_neg && flags->dot_val))
		len += 1;
	if (flags->has_neg && !flags->has_dot)
		fill_space(' ', (flags->len_field - len), count);
	else if (flags->has_dot && flags->len_is_neg && !flags->has_star)
		fill_space(' ', (flags->len_field - len), count);
	else if (flags->has_neg && flags->dot_val)
	{
		if (arg < 0 && (flags->type == 'd' || flags->type == 'i'))
			flags->dot_val -= 1;
		if (flags->len_is_neg)
			fill_space(' ', (flags->dot_val - len), count);
		else
		{
			if (flags->len_field < len)
				flags->len_field = len;
			if ((flags->dot_val - flags->len_field) > 0
				&& flags->type == 'p' && flags->len_field > len)
				fill_space(' ', (flags->dot_val - flags->len_field - 2), count);
			else if ((flags->dot_val - flags->len_field) > 0)
				fill_space(' ', (flags->dot_val - flags->len_field), count);
		}
	}
}
