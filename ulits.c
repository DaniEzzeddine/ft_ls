/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:21:08 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/05 21:57:39 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					free_link(t_info templink)
{
	free(templink.name);
	free(templink.path);
}

void					free_list(struct s_global_list **all_files)
{
	t_global_list		*templink;

	while (*all_files)
	{
		templink = *all_files;
		if (templink->info.name)
			ft_memdel((void**)&(templink->info.name));
		if (templink->info.path)
			ft_memdel((void**)&(templink->info.path));
		(*all_files) = (*all_files)->next;
		ft_memdel((void**)&(templink));
	}
}

t_info					build_struct_info(char *name, char *path)
{
	t_info				templink;
	struct stat			filestat;

	if (name[0])
	{
		templink.path = ft_strjoin(ft_strjoin(ft_strdup(path),\
		ft_strdup("/")), ft_strdup(name));
	}
	else
		templink.path = ft_strdup(path);
	templink.name = ft_strdup(name);
	if ((lstat(templink.path, &filestat) != -1) && S_ISDIR(filestat.st_mode))
		templink.isfile = 0;
	else
		templink.isfile = 1;
	templink.filestat = filestat;
	templink.time = filestat.st_mtimespec.tv_nsec;
	return (templink);
}


void					free_reit(DIR *directory, struct s_global_list **allfiles)
{
	closedir(directory);
	free_list(allfiles);
	free(allfiles);
}