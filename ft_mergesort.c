/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:45:09 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/02/28 18:16:47 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void							ft_mergesort(struct s_global_list **headref)
{
	t_global_list				*head;
	t_global_list				*a;
	t_global_list				*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_frontbacksplit(head, &a, &b);
	ft_mergesort(&a);
	ft_mergesort(&b);
	*headref = ft_sortedmerge(a, b);
}

struct s_global_list			*ft_sortedmerge(struct s_global_list *a,\
struct s_global_list *b)
{
	t_global_list				*result;

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

void							ft_frontbacksplit(struct s_global_list *source,\
struct s_global_list **frontref, struct s_global_list **backref)
{
	t_global_list				*fast;
	t_global_list				*slow;

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
