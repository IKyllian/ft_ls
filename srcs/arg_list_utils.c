/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:15:39 by kdelport          #+#    #+#             */
/*   Updated: 2023/04/03 11:16:31 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arg_list	*create_arg(char *arg, int is_file)
{
	t_arg_list	*new;
	struct stat	stat_buffer;

	if (lstat(arg, &stat_buffer) < 0)
	{
		ft_printf("Error while Stat\n");
		return (NULL);
	}
	new = (t_arg_list *)malloc(sizeof(t_arg_list));
	if (!new)
		return (NULL);
	new->dir_name = ft_strdup(arg);
	new->is_file = is_file;
	new->dir_stat = stat_buffer;
	new->next = NULL;
	return (new);
}

t_arg_list	*add_sort(t_arg_list **list, t_arg_list **last, \
	t_arg_list **begin, t_arg_list **new)
{
	(*new)->next = *list;
	if ((*last) != NULL)
	{
		(*last)->next = (*new);
		return (*begin);
	}
	return (*new);
}

t_arg_list	*first_arg_node(t_arg_list **arg_list, t_arg_list **new)
{
	*arg_list = *new;
	return (*new);
}

t_arg_list	*add_arg(char *path, int is_file, \
	t_arg_list **arg_list, t_options options)
{
	t_arg_list	*list;
	t_arg_list	*last;
	t_arg_list	*new;
	t_arg_list	*begin;

	list = *arg_list;
	begin = *arg_list;
	last = NULL;
	new = create_arg(path, is_file);
	if (!new)
		return (NULL);
	if (*arg_list == NULL)
		return (first_arg_node(arg_list, &new));
	while (list)
	{
		if ((sort_arg_by_time(new, list, options)) || (!options.sort_time
				&& sort_arg_by_letter(new, list, options.reverse)))
			return (add_sort(&list, &last, &begin, &new));
		last = list;
		list = list->next;
	}
	last->next = new;
	return (begin);
}
