/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:11:45 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:26:31 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <getopt.h>
# include <grp.h>
# include <pwd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sysexits.h>
# include <stdint.h>
# include <time.h>
# include <limits.h>
# include <unistd.h>
# include "./libft/libft.h"

int					g_total;

typedef struct				s_info
{
	unsigned char			isfile;
	char					*path;
	char					*name;
	struct stat				filestat;
	time_t					time;
	int						x;
}							t_info;

typedef struct				s_file_list
{
	struct s_info			info;
	struct s_file_list		*next;
}							t_file_list;

typedef struct				s_flags
{
	bool					r;
	bool					t;
	bool					c_r;
	bool					a;
	bool					l;
	int						i;
}							t_flags;

void						sort_print(t_file_list *files);
void						get_sort(t_file_list **all_files);
void						ft_mergesort(t_file_list **headref);
t_file_list					*ft_sortedmerge(t_file_list *a,\
t_file_list *b);
void						ft_frontbacksplit(t_file_list *source,\
t_file_list **frontref, t_file_list **backref);
int							time_sort(t_file_list *one, t_file_list *two);
void						print_list(t_file_list *all_files);
void						open_dirs(int argc, t_file_list *dirs);
void						ft_recursive(int argc, t_file_list *all_files);
t_flags						ft_parse_flags(int argc, char **argv);
void						free_list(t_file_list *node);

void						ft_lstpush_file(t_file_list **lst,\
t_file_list *new);
t_file_list					*ft_lstnew_file(t_info info);

t_info						get_info(char *path, char *name);

int							is_file_exists(const char *path);
void						wrong_usage();

void						quick_sort(char **files, int left, int right);

int					g_max;
t_flags				g_flags;
#endif
