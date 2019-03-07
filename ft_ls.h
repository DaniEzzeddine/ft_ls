/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:11:59 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/05 16:16:52 by dezzeddi         ###   ########.fr       */
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

extern int					g_total;

typedef struct				s_info
{
	unsigned char			isfile;
	char					*path;
	char					*name;
	struct stat				filestat;
	time_t					time;
	int						x;
}							t_info;

typedef struct				s_global_list
{
	struct s_info			info;
	struct s_global_list	*next;
}							t_global_list;

typedef struct				s_flags
{
	bool					r;
	bool					t;
	bool					c_r;
	bool					a;
	bool					l;
}							t_flags;

void						free_link(t_info templink);
void						ft_lstpush_folder(t_global_list **lst,
							t_global_list *new);
t_global_list				*ft_lstnew_folder(t_info templink);
void						get_sort(t_flags flags, t_global_list **all_files);
void						ft_recursive(t_flags flags, t_info prevfolder);
void						ft_iterative(t_flags flags, t_info prevfolder);
void						print_list(t_flags flags,
							t_global_list **all_files);
t_info						build_struct_info(char *name, char *path);
void						get_dirs(t_flags flags,
							t_global_list **all_files);
struct s_global_list		*ft_sortedmerge(struct s_global_list *a,
							struct s_global_list *b);
void						ft_frontbacksplit(struct s_global_list *source,
							struct s_global_list **frontref,
							struct s_global_list **backref);
void						free_list(struct s_global_list **all_files);
void						ft_mergesort(struct s_global_list **headref);
int							time_sort(t_global_list *one, t_global_list *two);
void						free_reit(DIR *directory, struct s_global_list **allfiles);

#endif
