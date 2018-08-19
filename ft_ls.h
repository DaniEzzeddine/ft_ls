/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 15:11:59 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/08/07 21:22:02 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
# include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "./libft/libft.h"

size_t ft_printf(char *format, ...);

typedef struct s_info
{
	bool		isfile;
	char		*path;
	char		*name;
	struct stat filestat;
	time_t		time;
	int			level;
}				t_info;

typedef struct s_global_list
{
	struct s_info			info;
	struct s_global_list	*next;
} t_global_list;


	typedef struct s_flags
{
	bool r;
	bool t;
	bool c_r;
	bool a;
	bool l;
} t_flags;

void		ft_lstpush_folder(t_global_list **lst, t_global_list *new);
t_global_list		*ft_lstnew_folder(t_info templink);
#endif
