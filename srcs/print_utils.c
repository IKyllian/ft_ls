/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:52:36 by kdelport          #+#    #+#             */
/*   Updated: 2024/01/10 10:53:38 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_file_attributes(t_dirInfos *dir)
{
	char	buff2[101];

	if (listxattr(dir->path, buff2, sizeof(buff2)) > 0)
		return ('@');
	return (' ');
}
