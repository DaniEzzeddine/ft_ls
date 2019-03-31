/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfuncs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:15:20 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:25:29 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						ft_lstpush_file(t_file_list **lst, t_file_list *new)
{
	t_file_list	*current;

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

t_file_list					*ft_lstnew_file(t_info info)
{
	t_file_list		*new;

	new = (t_file_list *)malloc(sizeof(t_file_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->info = info;
	if (g_max < (int)ft_strlen(new->info.name))
		g_max = ft_strlen(new->info.name);
	return (new);
}

t_info						get_info(char *path, char *name)
{
	t_info				file_info;
	struct stat			filestat;

	file_info.name = ft_strdup(name);
	if (!ft_strcmp(path, ""))
		file_info.path = ft_strdup(name);
	else if (!ft_strcmp(name, ""))
		file_info.path = ft_strdup(path);
	else
		file_info.path = ft_strjoin(ft_strjoin(ft_strdup(path),\
		ft_strdup("/")), ft_strdup(name));
	if ((lstat(file_info.path, &filestat) != -1) && S_ISDIR(filestat.st_mode))
		file_info.isfile = 0;
	else
		file_info.isfile = 1;
	file_info.filestat = filestat;
	g_total += filestat.st_blocks;
	file_info.time = filestat.st_mtimespec.tv_nsec;
	return (file_info);
}
