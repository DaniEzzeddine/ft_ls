/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:56:50 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/08/07 22:15:36 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_permissions(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');
	printf("   ");
}

void print_list(t_flags flags, t_global_list **all_files)
{
	t_global_list *tempfolder;
	t_file_list		*tempfile;

	while ((*all_files)->next)
	{
		printf("%s:\n", (*all_files)->info.name);
		tempfile = (*all_files)->files;
		while (tempfile->next)
		{
			printf("\t%s,\n", tempfile->content);
			tempfile = tempfile->next;
		}
		tempfolder = (*all_files)->folders;
		while (tempfolder->next)
		{
			printf("\t");
			print_list(flags, &tempfolder);
			tempfolder = tempfolder->next;
		}
	}
}

t_flags parse_flags(int argc, char **argv)
{
	t_flags flags;
	char ch;

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
	}
	return (flags);
}

void ft_iterative(int argc, char **argv, t_flags flags, char *path)
{
	struct dirent *file;
	DIR *direct;
	t_list *all_files;

	direct = opendir(path);
	while ((file = readdir(direct)))
	{
		ft_lstpush(&all_files, ft_lstnew((void *)file, sizeof(struct dirent)));
	}
}

void ft_recursive(t_global_list **all_files, t_flags flags, char *path)
{
	DIR *directory;
	struct dirent *file;
	struct stat fileStat;
	t_info	templink;

	(*all_files) = (t_global_list *)ft_memalloc(sizeof(t_global_list));
	if ((directory = opendir(path)))
	{
		while ((file = readdir(directory)))
		{
			if (file->d_name[0] != '.')
			{
				templink.path = ft_strjoin(ft_strjoin(ft_strdup(path), ft_strdup("/")), ft_strdup(file->d_name));
				templink.name = ft_strdup(file->d_name);
				stat(templink.path, &fileStat);
				if (S_ISDIR(fileStat.st_mode))
				{
					ft_lstpush_global(all_files, ft_lstnew_folder(templink));
					ft_recursive(&((*all_files)->folders), flags, templink.path);

				}
				else
				{
					ft_lstpush_file(all_files, ft_lstnew_file(templink));

				}
			}
		}
		// temp = (*all_files)->content;
		// printf("%s:\n", temp->content);
		// temp = temp->next;
		// while (temp->next)
		// {
		// 	printf("\t%s\n", temp->content);
		// 	temp = temp->next;
		// }
	}
}

// struct dirent	*file;
// DIR				*direct;
// char			*temppath;
// t_data			*files_in_dir;
// struct stat		fileStat;
// t_data			temp;

// files_in_dir =ft_memalloc(sizeof(t_data*));
// stat(path, &fileStat);
// if ((direct = opendir(path)) && (S_ISDIR(fileStat.st_mode)))
// {
// 	files_in_dir->name_of_the_folder = ft_strdup(path);
// 	while ((file = readdir(direct)))
// 	{
// 		if (file->d_name[0] != '.')
// 		{
// 			temppath = ft_strjoin(ft_strdup(path), ft_strdup("/"));
// 			temppath = ft_strjoin(temppath, ft_strdup(file->d_name));
// 			ft_lstadd(&(files_in_dir->files_in_folder), ft_lstnew(temppath, ft_strlen(temppath)));
// 			printf("%s\n", temppath);
// 			ft_recursive(all_files, flags, temppath);
// 		}
// 	}
// 	ft_lstadd(all_files, ft_lstnew(&files_in_dir, sizeof(t_data*)));
// 	while((*all_files)->next)
// 	{
// 		ft_memcpy((void *)(&temp), (*all_files)->content, sizeof(t_data));
// 		printf("%s", temp.name_of_the_folder);
// 		(*all_files) = (*all_files)->next;
// 	}
// free(files_in_dir);
// closedir(direct);
// }

int main(int argc, char **argv)
{
	t_flags flags;
	int i;
	t_global_list **all_files;
	t_info	templink;

	flags = parse_flags(argc, argv);
	i = optind;
	all_files = (t_global_list **)ft_memalloc(sizeof(t_global_list*));
	(*all_files) = (t_global_list *)ft_memalloc(sizeof(t_global_list));
	while (i <= argc)
	{
		if (!argv[i])
			templink.name = ft_strdup(".");
		else
			templink.path = ft_strjoin(ft_strdup("./"), ft_strdup(argv[i]));
		if (flags.c_r)
		{
			ft_lstpush_global(all_files, ft_lstnew_folder(templink));
			ft_recursive(&((*all_files)->folders), flags, templink.name);
		}
		else
			ft_iterative(argc, argv, flags, templink.name);
		i++;
	}
	print_list(flags, all_files);
	return (0);
}