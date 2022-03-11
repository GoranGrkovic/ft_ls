/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:17:44 by gogrkovi          #+#    #+#             */
/*   Updated: 2019/10/10 14:37:56 by gogrkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_size_errorhandling(t_size *size, t_elem *cur)
{
	char *str1;

	str1 = NULL;
	if (getpwuid(cur->st_uid))
		size->userspace = (int)ft_strlen(getpwuid(cur->st_uid)->pw_name) \
			> size->userspace ? (int)ft_strlen(getpwuid(cur->st_uid)->pw_name) \
				: size->userspace;
	else
	{
		str1 = ft_itoa(cur->st_uid);
		size->userspace = (int)ft_strlen(str1) > size->userspace \
			? (int)ft_strlen(str1) : size->userspace;
	}
	str1 ? free(str1) : 0;
	if (getgrgid(cur->st_gid))
		size->groupspace = (int)ft_strlen(getgrgid(cur->st_gid)->gr_name) \
			> size->groupspace ? \
			(int)ft_strlen(getgrgid(cur->st_gid)->gr_name) : size->groupspace;
	else
	{
		str1 = ft_itoa(cur->st_gid);
		size->groupspace = (int)ft_strlen(str1) > size->groupspace \
			? (int)ft_strlen(str1) : size->groupspace;
	}
	str1 ? free(str1) : 0;
}

void	get_size_quick(t_size *size, t_elem *cur)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;

	str1 = ft_itoa(cur->st_nlink);
	str2 = ft_itoa(major(cur->st_rdev));
	str3 = ft_itoa(minor(cur->st_rdev));
	str4 = ft_itoa(cur->st_size);
	size->linkspace = (int)ft_strlen(str1) > size->linkspace \
						? (int)ft_strlen(str1) : size->linkspace;
	size->maj = (int)ft_strlen(str2) > size->maj \
				? (int)ft_strlen(str2) : size->maj;
	size->min = (int)ft_strlen(str3) > size->min \
				? (int)ft_strlen(str3) : size->min;
	size->size = (int)ft_strlen(str4) > size->size \
				? (int)ft_strlen(str4) : size->size;
	size->total += cur->st_blocks;
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

t_size	get_size(t_opt arg, t_elem *files)
{
	t_elem	*cur;
	t_size	size;

	size = (t_size){0, 0, 0, 0, 0, 0, 0};
	cur = files;
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
		{
			get_size_quick(&size, cur);
			get_size_errorhandling(&size, cur);
		}
		cur = cur->next;
	}
	return (size);
}
