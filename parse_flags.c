/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:27:43 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:29:39 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				set_flag(t_flags *flags, char flag)
{
	if (flag == 'l')
		flags->l = true;
	else if (flag == 'R')
		flags->c_r = true;
	else if (flag == 'r')
		flags->r = true;
	else if (flag == 'a')
		flags->a = true;
	else if (flag == 't')
		flags->t = true;
	else
		return (0);
	return (1);
}

t_flags			ft_parse_flags(int argc, char **argv)
{
	int			i;
	t_flags		flags;

	i = 1;
	ft_bzero(&flags, sizeof(flags));
	if (argc > 1)
	{
		while (argv[i] && argv[i][0] == '-')
		{
			while (*(++argv[i]))
				if (!set_flag(&flags, *argv[i]))
				{
					ft_printf("ft_ls: illegal option -- %c\n", *argv[i]);
					wrong_usage();
				}
			i++;
		}
	}
	flags.i = i;
	return (flags);
}
