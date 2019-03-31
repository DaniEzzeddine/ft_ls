/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:45:09 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:16:13 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void							ft_mergesort(t_file_list **headref)
{
	t_file_list				*head;
	t_file_list				*a;
	t_file_list				*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_frontbacksplit(head, &a, &b);
	ft_mergesort(&a);
	ft_mergesort(&b);
	*headref = ft_sortedmerge(a, b);
}

t_file_list						*ft_sortedmerge(t_file_list *a,\
t_file_list *b)
{
	t_file_list				*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (time_sort(a, b))
	{
		result = a;
		result->next = ft_sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = ft_sortedmerge(a, b->next);
	}
	return (result);
}

void							ft_frontbacksplit(t_file_list *source,\
t_file_list **frontref, t_file_list **backref)
{
	t_file_list				*fast;
	t_file_list				*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}
