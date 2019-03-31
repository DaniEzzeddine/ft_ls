/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:17:56 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:39:56 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					ft_recursive(int argc, t_file_list *all_files)
{
	t_file_list *dirs;

	dirs = NULL;
	while (all_files)
	{
		if (!(all_files->info.isfile) && (ft_strcmp(all_files->info.name, "."))\
		&& (ft_strcmp(all_files->info.name, "..")))
			ft_lstpush_file(&dirs, ft_lstnew_file\
(get_info(all_files->info.path, "")));
		all_files = all_files->next;
	}
	open_dirs(argc + 1, dirs);
	free_list(dirs);
}

t_file_list				*open_single_dir(int argc, t_file_list *dirs)
{
	DIR				*directory;
	struct dirent	*file;
	t_file_list		*all_files;

	all_files = NULL;
	if ((directory = opendir(dirs->info.path)))
	{
		g_total = 0;
		if (argc > 2 && ft_strcmp(dirs->info.path, ".") &&\
ft_strcmp(dirs->info.path, ".."))
			ft_printf("\n%s:\n", dirs->info.path);
		while ((file = readdir(directory)))
			if (file->d_name[0] != '.' || g_flags.a)
				ft_lstpush_file(&all_files, ft_lstnew_file\
(get_info(dirs->info.path, file->d_name)));
		closedir(directory);
		return (all_files);
	}
	return (NULL);
}

void					open_dirs(int argc, t_file_list *dirs)
{
	t_file_list		*all_files;

	all_files = NULL;
	while (dirs)
	{
		all_files = open_single_dir(argc, dirs);
		if (all_files)
			sort_print(all_files);
		if (g_flags.c_r)
			ft_recursive(argc, all_files);
		free_list(all_files);
		all_files = NULL;
		dirs = dirs->next;
	}
}
