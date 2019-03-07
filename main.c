/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:44:32 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/05 19:23:44 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int g_total;

t_flags					ls_parse_flags(int argc, char **argv)
{
	t_flags		flags;
	char		ch;

	ft_bzero(&flags, sizeof(t_flags));
	while ((ch = getopt(argc, argv, "lRtar")) != -1)
	{
		if (ch == 'r')
			flags.r = true;
		else if (ch == 'l')
			flags.l = true;
		else if (ch == 'a')
			flags.a = true;
		else if (ch == 't')
			flags.t = true;
		else if (ch == 'R')
			flags.c_r = true;
		else
		{
			exit(0);
			ft_printf("usage: ls [-ltarR] [file ...]");
		}
	}
	return (flags);
}

int						is_file_exists(const char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

void					sort_print(t_flags flags, t_global_list *files)
{
	get_sort(flags, &files);
	print_list(flags, &files);
}

void					fill_list(struct s_global_list *all_files, struct s_global_list **files, struct s_global_list **folders)
{
	while (all_files)
	{
		if (!(is_file_exists(all_files->info.path)))
			write(2, ft_strjoin(ft_strdup(all_files->info.name), ft_strdup\
(": No such file or directory\n")), ft_strlen(all_files->info.name) + 28);
		else if (all_files->info.isfile)
			ft_lstpush_folder(files, ft_lstnew_folder(all_files->info));
		else
			ft_lstpush_folder(folders, ft_lstnew_folder(all_files->info));
		all_files = all_files->next;
	}
}

void					ls_main_loop(void (*f)(t_flags, t_info),\
t_global_list *all_files, t_flags flags)
{
	t_global_list	*files;
	t_global_list	*folders;
	t_global_list	*temp;

	folders = NULL;
	files = NULL;
	fill_list(all_files, &files, &folders);
	if (files)
	{
		sort_print(flags, files);
		free_list(&files);
	}
	temp = folders;
	while (temp)
	{
		ft_printf("%s:\n", temp->info.name);
		f(flags, temp->info);
		temp = temp->next;
	}
	// free(all_files);
	free_list(&folders);
}


int						main(int argc, char **argv)
{
	t_flags				flags;
	int					i;
	t_info				info;
	t_global_list		*all_files = 0;

	flags = ls_parse_flags(argc, argv);
	i = optind - 1;
	if (!argv[++i])
	{
		info = build_struct_info(".", ".");
		ft_lstpush_folder(&all_files, ft_lstnew_folder(info));
	}
	else
		while (i < argc)
		{
			g_total = 0;
			info = build_struct_info("",argv[i]);
			ft_lstpush_folder(&all_files, ft_lstnew_folder(info));
			i++;
		}
	if (flags.c_r)
		ls_main_loop(ft_recursive, all_files, flags);
	else
		ls_main_loop(ft_iterative, all_files, flags);
	
	while(true);
	return (0);
}
