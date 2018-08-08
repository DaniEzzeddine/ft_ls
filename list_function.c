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
 void	ft_lstpush_global(t_global_list **lst, t_global_list *new)
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
	while (current->folders)
		current = current->folders;
	current->folders = new;
}
t_file_list			*ft_lstnew_file(t_info templink)
{
	t_file_list		*new;

	new = (t_file_list *)malloc(sizeof(t_file_list));
	new->content = templink.name;
	new->next = NULL;
	return(new);
}

t_global_list		*ft_lstnew_folder(t_info templink)
{
	t_global_list *new;

	new = (t_global_list *)malloc(sizeof(t_global_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->files = NULL;
	new->folders = NULL;
	ft_memcpy(&(new->info), &templink, sizeof(t_info));
	return (new);
}

void		ft_lstpush_file(t_global_list **lst, t_file_list *new)	
{
	t_file_list *current;

	if (!lst)
		return ;
	current = (*lst)->files;
	if (!current)
	{
		(*lst)->files = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}