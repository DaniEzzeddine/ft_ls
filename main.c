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

void ft_recursive(t_flags flags,t_info prevfolder);

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

int ft_count_max_length(t_global_list **all_files)
{
	int max_length;
	t_global_list *temp;
	t_info info;

	max_length = 0;
	temp = *all_files;
	while (temp)
	{
		info = temp->info;
		if (ft_strlen(info.name) > max_length)
			max_length = ft_strlen(info.name);
		temp = temp->next;
	}
	return (max_length);
}

void print_list(t_flags flags, t_global_list **all_files)
{
	t_global_list 	*tempfolder;
	t_info			info;
	int				max_length;

	max_length = 0;
	tempfolder = (*all_files);
	max_length = ft_count_max_length(all_files);
	while (tempfolder)
	{
		info = tempfolder->info;
		printf("%*s",max_length, info.name);
		tempfolder = tempfolder->next;
	}
}
void swap(t_global_list *p1, t_global_list *p2)
{
	t_info temp;

	temp = p1->info;		
	p1->info = p2->info;
	p2->info = temp; 
}

void selection_sort(struct s_global_list *head)
{
	t_global_list *traverse;
	t_global_list *start;
	t_global_list *min;
	t_info			 	min_data;
	t_info			traverse_data;
 
	start = head;
    while (start->next)
    {
		// printf("%s\n", start->info.name);
		min = start;
		traverse = start->next;
		while(traverse)
		{
			min_data = min->info;
			traverse_data = traverse->info;
			if (min_data.time < traverse_data.time)
				min = traverse;
			traverse = traverse->next;
		}
		swap(start, min);
		start = start->next;
	}
	printf("\n");
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

void ft_iterative(t_flags flags, t_info prevfolder)
{
	DIR *directory;
	struct dirent *file;
	struct stat filestat;
	t_info	templink;
	t_global_list	**all_files;

	all_files = (t_global_list**)ft_memalloc(sizeof(t_global_list*));	
	if ((directory = opendir(prevfolder.path)))
	{
		while ((file = readdir(directory)))
		{
			templink.path = ft_strjoin(ft_strjoin(ft_strdup(prevfolder.path), ft_strdup("/")), ft_strdup(file->d_name));
			templink.name = ft_strdup(file->d_name);
			if ((stat(templink.path, &filestat) != -1) && S_ISDIR(filestat.st_mode))
				templink.isfile = false;
			else
				templink.isfile = true;
			templink.filestat = filestat;
			templink.time = filestat.st_mtime;
			templink.level = prevfolder.level + 1;
			if (templink.name[0] != '.' || flags.a)
				ft_lstpush_folder(all_files, ft_lstnew_folder(templink));
		}
	if (flags.t)
		selection_sort(*all_files);
	print_list(flags, all_files);
	}
}


void filedir_sort(t_flags flags, t_global_list **all_files)
{
	t_global_list *start;

	start = (*all_files);
	while(start)
	{
		if (!(start->info.isfile) && (ft_strcmp(start->info.name,".")) && (ft_strcmp(start->info.name,"..")))
		{
			printf("\n%s:\n", start->info.path);
			ft_recursive(flags, start->info);
		}
		start = start->next;
	}

}

void ft_recursive(t_flags flags,t_info prevfolder)
{
	DIR *directory;
	struct dirent *file;
	struct stat filestat;
	t_info	templink;
	t_global_list	**all_files;

	all_files = (t_global_list**)ft_memalloc(sizeof(t_global_list*));	
	if ((directory = opendir(prevfolder.path)))
	{
		while ((file = readdir(directory)))
		{
			templink.path = ft_strjoin(ft_strjoin(ft_strdup(prevfolder.path), ft_strdup("/")), ft_strdup(file->d_name));
			templink.name = ft_strdup(file->d_name);
			if ((stat(templink.path, &filestat) != -1) && S_ISDIR(filestat.st_mode))
				templink.isfile = false;
			else
				templink.isfile = true;
			templink.filestat = filestat;
			templink.time = filestat.st_mtime;
			templink.level = prevfolder.level + 1;
			if (templink.name[0] != '.' || flags.a)
				ft_lstpush_folder(all_files, ft_lstnew_folder(templink));
		}
	if (flags.t)
		selection_sort(*all_files);
	print_list(flags, all_files);
	filedir_sort(flags, all_files);
	}
}


int main(int argc, char **argv)
{
	t_flags flags;
	int i;
	t_info	templink;

	
	flags = parse_flags(argc, argv);
	i = optind;
	while (i <= argc)
	{
		if (!argv[i])
			templink.name = ft_strdup(".");
		else
			templink.name = ft_strdup(argv[i]);
		templink.path = templink.name;
		templink.level = 0;
		printf("\n%s:\n", templink.path);
		if (flags.c_r)
			ft_recursive(flags, templink);
		else
			ft_iterative(flags, templink);
		i++;
	}
	return (0);
}