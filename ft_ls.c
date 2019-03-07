/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:45:16 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/05 19:20:19 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void				ft_iterative(t_flags flags, t_info prevfolder)
{
	DIR						*directory;
	struct dirent			*file;
	t_info					templink;
	t_global_list			**all_files;

	all_files = (t_global_list **)ft_memalloc(sizeof(t_global_list *));
	g_total = 0;
	if ((directory = opendir(prevfolder.path)))
	{
		while ((file = readdir(directory)))
		{
			if (file->d_name[0] != '.' || flags.a)
			{
				templink = build_struct_info(file->d_name, prevfolder.path);
				g_total += templink.filestat.st_blocks;
				ft_lstpush_folder(all_files, ft_lstnew_folder(templink));
			}
		}
	}
	get_sort(flags, all_files);
	if (flags.l)
		ft_printf("total %d\n", g_total);
	print_list(flags, all_files);
	free_reit(directory, all_files);
}

void				get_dirs(t_flags flags, t_global_list **all_files)
{
	t_global_list *start;

	start = (*all_files);
	g_total = 0;
	while (start)
	{
		if (!(start->info.isfile) && (ft_strcmp(start->info.name, "."))\
		&& (ft_strcmp(start->info.name, "..")))
		{
			if (start->info.name[0] != '.')
				ft_printf("\n%s:\n", start->info.path);
			ft_recursive(flags, start->info);
		}
		start = start->next;
	}
}

void				ft_recursive(t_flags flags, t_info prevfolder)
{
	DIR				*directory;
	struct dirent	*file;
	t_info			templink;
	t_global_list	**all_files;

	all_files = (t_global_list **)ft_memalloc(sizeof(t_global_list *));
	if ((directory = opendir(prevfolder.path)))
	{
		while ((file = readdir(directory)))
		{
			if (file->d_name[0] != '.' || flags.a)
			{
				templink = build_struct_info(file->d_name, prevfolder.path);
				g_total += templink.filestat.st_blocks;
				ft_lstpush_folder(all_files, ft_lstnew_folder(templink));
			}
		}
		get_sort(flags, all_files);
		if (flags.l)
			ft_printf("total %d\n", g_total);
		print_list(flags, all_files);
		get_dirs(flags, all_files);
		// free_reit(directory, all_files);
	}
}
