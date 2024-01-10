/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:47:42 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:02 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	integer_length(long nbr)
{
	int			length;
	long long	l_nbr;

	l_nbr = nbr;
	length = 0;
	if (l_nbr < 0)
		l_nbr *= -1;
	while (l_nbr >= 10)
	{
		length++;
		l_nbr /= 10;
	}
	return (++length);
}
