/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:44:47 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/02/28 16:44:50 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						swap(t_global_list *p1, t_global_list *p2)
{
	t_info	temp;

	temp = p1->info;
	p1->info = p2->info;
	p2->info = temp;
}

void						lex_sort(struct s_global_list *head)
{
	t_global_list		*traverse;
	t_global_list		*start;
	t_global_list		*max;

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

int							time_sort(t_global_list *one, t_global_list *two)
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

t_global_list				*ft_reverse_lst(t_global_list *lst)
{
	t_global_list		*a;
	t_global_list		*b;
	t_global_list		*c;

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

void						get_sort(t_flags flags, t_global_list **all_files)
{
	lex_sort(*all_files);
	if (flags.t)
		ft_mergesort(all_files);
	if (flags.r)
		*all_files = ft_reverse_lst(*all_files);
}
