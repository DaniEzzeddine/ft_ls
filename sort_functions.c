/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:44:47 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:31:05 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						swap(t_file_list *p1, t_file_list *p2)
{
	t_info	temp;

	temp = p1->info;
	p1->info = p2->info;
	p2->info = temp;
}

void						lex_sort(t_file_list *head)
{
	t_file_list		*traverse;
	t_file_list		*start;
	t_file_list		*max;

	start = head;
	while (start->next)
	{
		max = start;
		traverse = start->next;
		while (traverse)
		{
			if (ft_strcmp(max->info.name, traverse->info.name) > 0)
				max = traverse;
			traverse = traverse->next;
		}
		swap(start, max);
		start = start->next;
	}
}

int							time_sort(t_file_list *one, t_file_list *two)
{
	if (one->info.filestat.st_mtimespec.tv_sec ==
			two->info.filestat.st_mtimespec.tv_sec)
	{
		if (one->info.filestat.st_mtimespec.tv_nsec ==
				two->info.filestat.st_mtimespec.tv_nsec)
			return (ft_strcmp(one->info.name, two->info.name) < 0);
		else
			return (one->info.filestat.st_mtimespec.tv_nsec >
					two->info.filestat.st_mtimespec.tv_nsec);
	}
	return (one->info.filestat.st_mtimespec.tv_sec >
			two->info.filestat.st_mtimespec.tv_sec);
}

t_file_list					*ft_reverse_lst(t_file_list *lst)
{
	t_file_list		*a;
	t_file_list		*b;
	t_file_list		*c;

	a = NULL;
	b = lst;
	c = (lst)->next;
	while (b)
	{
		c = b->next;
		b->next = a;
		a = b;
		b = c;
	}
	return (a);
}

void						get_sort(t_file_list **all_files)
{
	lex_sort(*all_files);
	if (g_flags.t)
		ft_mergesort(all_files);
	if (g_flags.r)
		*all_files = ft_reverse_lst(*all_files);
}
