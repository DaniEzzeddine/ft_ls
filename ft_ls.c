/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:08:21 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:25:01 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file_list				*get_files(t_file_list *files,\
char **argv, int i)
{
	int	j;

	j = 0;
	while (argv[i])
	{
		ft_lstpush_file(&files, ft_lstnew_file(get_info("", argv[i])));
		i++;
		j++;
	}
	if (j == 0)
		ft_lstpush_file(&files, ft_lstnew_file(get_info("", ".")));
	return (files);
}

void							sort_print(t_file_list *files)
{
	get_sort(&files);
	print_list(files);
}

void							render_files(char **non_files, int argc,\
t_file_list *files, t_file_list *dirs)
{
	while (*non_files)
	{
		ft_printf("ls: %s: No such file or directory\n", *non_files);
		free(*non_files);
		non_files++;
	}
	if (files)
	{
		sort_print(files);
		ft_printf("\n");
		free_list(files);
	}
	if (dirs)
	{
		open_dirs(argc, dirs);
		free_list(dirs);
	}
}

void							file_dir_sort(int argc, t_file_list *all_files)
{
	char			*not_files[argc];
	t_file_list		*files;
	t_file_list		*dirs;
	int				i;

	i = 0;
	files = NULL;
	dirs = NULL;
	while (all_files)
	{
		if (!(is_file_exists(all_files->info.path)))
			not_files[i++] = ft_strdup(all_files->info.name);
		else if (all_files->info.isfile)
			ft_lstpush_file(&files, ft_lstnew_file(all_files->info));
		else
			ft_lstpush_file(&dirs, ft_lstnew_file(all_files->info));
		all_files = all_files->next;
	}
	quick_sort(not_files, 0, i - 1);
	not_files[i] = NULL;
	render_files(not_files, argc, files, dirs);
}

int								main(int argc, char **argv)
{
	int				i;
	t_file_list		*files;

	files = NULL;
	g_max = 0;
	g_flags = ft_parse_flags(argc, argv);
	i = g_flags.i;
	files = get_files(files, argv, i);
	file_dir_sort(argc, files);
}
