/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:11:27 by gogrkovi          #+#    #+#             */
/*   Updated: 2019/10/10 16:19:26 by gogrkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_color(mode_t mode)
{
	S_ISBLK(mode) ? ft_putstr(C_RED) : NULL;
	S_ISCHR(mode) ? ft_putstr(C_BLUE) : NULL;
	S_ISDIR(mode) ? ft_putstr(C_CYAN) : NULL;
	S_ISFIFO(mode) ? ft_putstr(C_BROWN) : NULL;
	S_ISREG(mode) ? ft_putstr(C_NONE) : NULL;
	S_ISLNK(mode) ? ft_putstr(C_GREEN) : NULL;
	S_ISSOCK(mode) ? ft_putstr(C_MAGENTA) : NULL;
}

void	ls_simple(t_opt arg, t_elem *files)
{
	t_elem	*cur;

	cur = files;
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
		{
			ft_color(cur->st_mode);
			ft_putendl(cur->name);
			ft_putstr(C_NONE);
		}
		cur = cur->next;
	}
}

void	ls_long_file(t_opt arg, t_elem *cur, t_size size)
{
	print_access(cur);
	print_int(cur->st_nlink, size.linkspace);
	if (arg.g == 0)
	{
		if (getpwuid(cur->st_uid))
			print_str(getpwuid(cur->st_uid)->pw_name, size.userspace);
		else
			print_str(ft_itoa(cur->st_uid), size.userspace);
	}
	if (getgrgid(cur->st_gid))
		print_str(getgrgid(cur->st_gid)->gr_name, size.groupspace);
	else
		print_str(ft_itoa(cur->st_gid), size.groupspace);
	if (S_ISCHR(cur->st_mode) || S_ISBLK(cur->st_mode))
		print_majmin(cur, size);
	else
		print_int(cur->st_size, size.size);
	display_date(cur->date);
	ft_color(cur->st_mode);
	ft_putendl(cur->name);
	ft_putstr(C_NONE);
}

void	ls_long(t_opt arg, t_elem *files, int fileordir)
{
	t_elem	*cur;
	t_size	size;

	cur = files;
	size = get_size(arg, files);
	if (fileordir)
	{
		ft_putstr("total ");
		ft_putnbr(size.total);
		ft_putchar('\n');
	}
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
			ls_long_file(arg, cur, size);
		cur = cur->next;
	}
}

void	freelist(t_elem *elem, t_list *list)
{
	t_elem *tmp_elem;
	t_list *tmp_list;

	tmp_elem = NULL;
	tmp_list = NULL;
	while (list)
	{
		tmp_list = list->next;
		free(list->content);
		free(list);
		list = tmp_list;
	}
	while (elem)
	{
		tmp_elem = elem->next;
		free(elem->name);
		free(elem->path);
		free(elem);
		elem = tmp_elem;
	}
}
