/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:56:31 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 14:02:39 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fill_struct_spaces(char **str, t_flags *flags)
{
	char	*nb_spaces;
	int		i;

	nb_spaces = malloc(sizeof(char) * (ft_count_numbers(str) + 1));
	if (!nb_spaces)
		return (1);
	i = 0;
	if (*(*str - 1) == '-' && *(*str - 2) == '.')
		nb_spaces[i++] = '-';
	while (*(*str) && (*(*str) >= 48 && *(*str) <= 57))
		nb_spaces[i++] = *(*str)++;
	nb_spaces[i] = 0;
	if (*(*str) == '.')
	{
		flags->has_dot = 1;
		flags->dot_val = ft_atoi(nb_spaces);
		(*str)++;
	}
	else
		flags->len_field = ft_atoi(nb_spaces);
	free(nb_spaces);
	return (0);
}

void	fill_struct_star(char **str, t_flags *flags, va_list list)
{
	int	nb;

	nb = va_arg(list, int);
	if (*(*str + 1) == '.')
	{
		flags->has_dot = 1;
		flags->dot_val = nb;
		(*str)++;
	}
	else
	{
		flags->len_field = nb;
		flags->has_star = 1;
	}
}

int	check_prefix(char **str, t_flags *flags, va_list list)
{
	while (*(*str) && is_flags(*(*str)))
	{
		if (*(*str) == '0' && !flags->has_neg && !flags->has_dot)
			flags->has_zero = 1;
		if (*(*str) == '-')
		{
			if (flags->has_zero)
				flags->has_zero = 0;
			flags->has_neg = 1;
		}
		if (*(*str) == '.')
			flags->has_dot = 1;
		if (*(*str) == '*')
			fill_struct_star(str, flags, list);
		if (*(*str) >= 48 && *(*str) <= 57)
		{
			if (fill_struct_spaces(str, flags) == 1)
				return (1);
		}
		else
			(*str)++;
	}
	return (0);
}

int	ft_display(char **str, va_list list, int *count)
{
	t_flags	flags;

	struct_initialize(&flags);
	if (is_flags(*(*str)))
		if (check_prefix(str, &flags, list) == 1)
			return (1);
	flags.type = *(*str);
	if (ft_convert(str, list, count, &flags) == 1)
		return (1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		count;
	char	*str;

	str = (char *)format;
	va_start(list, format);
	count = 0;
	while (*str)
	{
		if (*str != '%')
			ft_putchar(*str, &count);
		else
		{
			++str;
			if (*str && ft_display(&str, list, &count) == 1)
				return (-1);
		}
		if (*str)
			str++;
	}
	va_end(list);
	return (count);
}
