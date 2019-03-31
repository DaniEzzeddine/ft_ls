/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:44:58 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:30:50 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char				print_filetype(mode_t mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static char				print_fileacl(char path[PATH_MAX])
{
	acl_t	tmp;
	char	buf[101];

	if (listxattr(path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

static char				*permissions(mode_t mode)
{
	char *buf;

	buf = (char *)malloc(sizeof(char) * 10);
	buf[0] = ((mode & S_IRUSR) ? 'r' : '-');
	buf[1] = ((mode & S_IWUSR) ? 'w' : '-');
	buf[2] = ((mode & S_IXUSR) ? 'x' : '-');
	buf[3] = ((mode & S_IRGRP) ? 'r' : '-');
	buf[4] = ((mode & S_IWGRP) ? 'w' : '-');
	buf[5] = ((mode & S_IXGRP) ? 'x' : '-');
	buf[6] = ((mode & S_IROTH) ? 'r' : '-');
	buf[7] = ((mode & S_IWOTH) ? 'w' : '-');
	buf[8] = ((mode & S_IXOTH) ? 'x' : '-');
	buf[9] = '\0';
	return (buf);
}

void					print_permissions(t_info info)
{
	struct passwd		*pw;
	struct group		*gr;
	char				monthdaytime[30];
	char				buf[NAME_MAX + 1];
	char				*perms;

	ft_bzero(buf, NAME_MAX + 1);
	gr = getgrgid(info.filestat.st_gid);
	pw = getpwuid(info.filestat.st_uid);
	strftime(monthdaytime, 30, " %b %d %X",
	localtime(&(info.filestat.st_mtimespec.tv_sec)));
	perms = permissions(info.filestat.st_mode);
	ft_printf("%c%s%c%3d 	%s %s %5lli %.13s ",\
	print_filetype(info.filestat.st_mode), perms,\
	print_fileacl(info.path), info.filestat.st_nlink,\
	pw->pw_name, gr->gr_name, info.filestat.st_size, monthdaytime);
	if ((readlink(info.path, buf, NAME_MAX)) == -1)
		ft_printf("%s\n", info.name);
	else
		ft_printf("%s -> %s\n", info.name, buf);
	free(perms);
}

void					print_list(t_file_list *all_files)
{
	int				i;
	struct ttysize	ts;

	ioctl(0, TIOCGSIZE, &ts);
	i = 0;
	if (g_flags.l)
		ft_printf("total %d\n", g_total);
	while (all_files)
	{
		if (g_flags.l)
			print_permissions(all_files->info);
		else
			ft_printf("%-*s", g_max + 3, all_files->info.name);
		all_files = all_files->next;
		if (i == ((ts.ts_cols / (g_max + 3)) - 1) && !g_flags.l)
		{
			write(1, "\n", 1);
			i = 0;
		}
		i++;
	}
	write(1, "\n", 1);
	g_max = 0;
}
