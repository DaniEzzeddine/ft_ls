/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 02:31:15 by dezzeddi          #+#    #+#             */
/*   Updated: 2019/03/09 02:33:35 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					wrong_usage(void)
{
	ft_printf("usage: ls [-Rlatr] [file ...]\n");
	exit(1);
}

int						is_file_exists(const char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

void					ft_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void					quick_sort(char **files, int left, int right)
{
	int		l;
	int		r;
	char	*piv;

	l = left;
	r = right;
	piv = files[(left + right) / 2];
	while (l <= r)
	{
		while (ft_strcmp(files[l], piv) < 0)
			l++;
		while (ft_strcmp(files[r], piv) > 0)
			r--;
		if (l <= r)
			ft_swap(&(files[l++]), &(files[r--]));
	}
	if (left < r)
		quick_sort(files, left, r);
	if (right > l)
		quick_sort(files, l, right);
}

void					free_list(t_file_list *node)
{
	t_file_list	*temp;

	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->info.name);
		free(temp->info.path);
		free(temp);
	}
}
