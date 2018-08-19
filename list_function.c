/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 19:49:32 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/08/07 22:03:39 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_lstpush_folder(t_global_list **lst, t_global_list *new)
{
	t_global_list *current;
 	
	if (!lst)
		return ;
	current = *lst;
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

t_global_list		*ft_lstnew_folder(t_info templink)
{
	t_global_list *new;
	t_info			info;

	new = (t_global_list *)malloc(sizeof(t_global_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	info.path = ft_strdup(templink.path);
	info.name = ft_strdup(templink.name);
	info.isfile = templink.isfile;
	info.filestat = templink.filestat;
	info.time = templink.time;
	info.level = templink.level;
	new->info = info;
	
	return (new);
}
