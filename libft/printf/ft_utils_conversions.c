/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_conversions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:36:40 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 14:07:35 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	to_string(va_list list, int *count, t_flags flags)
{
	char	*str;
	int		len;

	check_space_is_neg(&flags);
	str = va_arg(list, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	operands_string_dot(flags, count, len);
	ope_space_string(flags, count, len);
	print_string(flags, count, str, len);
	ope_space_string_suff(flags, count, len);
}

void	to_decimal(va_list list, int *count, t_flags *flags)
{
	int	nbr;
	int	arg_len;

	check_space_is_neg(flags);
	nbr = va_arg(list, int);
	arg_len = integer_length(nbr);
	if (nbr == 0 && flags->has_dot && !flags->dot_val && !flags->len_field)
		return ;
	ope_dot(flags, count, nbr, &arg_len);
	ope_space(flags, count, nbr, &arg_len);
	if (nbr == 0 && ((flags->dot_val && !flags->len_field)
			|| (flags->len_is_neg && !flags->has_star)))
		ft_putchar(' ', count);
	else
		ft_putnbr(nbr, count);
	ope_space_suff(flags, count, nbr, arg_len);
}

void	to_unsigned_decimal(va_list list, int *count, t_flags *flags)
{
	unsigned long long	nbr;
	int					arg_len;

	check_space_is_neg(flags);
	nbr = (unsigned int)va_arg(list, int);
	arg_len = u_nbr_len(nbr, 10);
	if (nbr == 0 && flags->has_dot && !flags->dot_val && !flags->len_field)
		return ;
	ope_dot(flags, count, 1, &arg_len);
	ope_space(flags, count, 1, &arg_len);
	if (nbr == 0 && ((flags->dot_val && !flags->len_field)
			|| (flags->len_is_neg && !flags->has_star)))
		ft_putchar(' ', count);
	else
		ft_unsigned_putnbr(nbr, count);
	ope_space_suff(flags, count, 1, arg_len);
}

int	to_hexa(va_list list, int *count, int is_min, t_flags *flags)
{
	unsigned long long	nbr;
	int					arg_len;

	check_space_is_neg(flags);
	nbr = (unsigned int)va_arg(list, int);
	arg_len = u_nbr_len(nbr, 16);
	if (nbr == 0 && flags->has_dot && !flags->dot_val && !flags->len_field)
		return (0);
	ope_dot(flags, count, 1, &arg_len);
	ope_space(flags, count, 1, &arg_len);
	if (nbr == 0 && flags->dot_val && !flags->len_field)
		ft_putchar(' ', count);
	else
	{
		if (ft_itoh(nbr, is_min, count, flags) == 1)
			return (1);
	}
	ope_space_suff(flags, count, 1, arg_len);
	return (0);
}

int	to_pointer_address(va_list list, int *count, t_flags *flags)
{
	void	*input;
	int		arg_len;

	check_space_is_neg(flags);
	input = (void *)va_arg(list, void *);
	arg_len = u_nbr_len((unsigned long long)input, 16) + 2;
	if (!(char *)input && flags->has_dot
		&& !flags->dot_val && !flags->len_field)
	{
		ft_putstr("0x", count);
		return (0);
	}
	ope_dot_address(flags, count, 1, &arg_len);
	ope_space(flags, count, 1, &arg_len);
	print_neg(*(int *)input, count, flags, &arg_len);
	if (ft_itoh((unsigned long long)input, 1, count, flags) == 1)
		return (1);
	ope_space_suff(flags, count, 1, arg_len);
	return (0);
}
