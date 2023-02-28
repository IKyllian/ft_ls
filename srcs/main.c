/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:34:53 by kdelport          #+#    #+#             */
/*   Updated: 2023/02/28 10:31:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{	
	int			path_index;
	t_dirInfos	*dir_list;
	t_datas		datas;

	dir_list = NULL;
	path_index = -1;
	main_struct_init(&datas);
	if (ac > 1)
		path_index = parser(av, &datas.options);
	if (path_index == -2)
		return (-1);
	if (path_index > 0)
		dir_list = read_dir(&datas, av[path_index], 0, &dir_list);
	else
		dir_list = read_dir(&datas, ".", 0, &dir_list);
	if (dir_list == NULL)
		return (-1);
	print_list(&dir_list, &datas, 0);
	free_lst(&dir_list);
	return (0);
}
