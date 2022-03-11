/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:29:55 by gogrkovi          #+#    #+#             */
/*   Updated: 2019/10/10 14:54:52 by gogrkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_file(t_opt arg, t_elem *files, int fileordir)
{
	t_elem	*cur;

	cur = files;
	cur = sort_elem(cur, arg);
	(arg.l == 1 || arg.g == 1) ? \
			ls_long(arg, cur, fileordir) : ls_simple(arg, cur);
	arg.upper_r == 1 ? recursion(arg, cur) : NULL;
}

void	do_ls_dir2(t_opt arg, t_elem *dirlist, int multidir)
{
	DIR		*dir;
	t_elem	*files;
	int		first;

	first = 0;
	files = NULL;
	while (dirlist)
	{
		dir = opendir(dirlist->name);
		while (elemget(&files, readdir(dir), \
			ft_strjoin(dirlist->path, "/"), arg) != 0)
			first = 0;
		closedir(dir);
		if (files)
		{
			first == 1 ? ft_putchar('\n') : NULL;
			multidir ? ft_putendl(ft_strjoin(dirlist->name, ":")) : NULL;
			first = 1;
			display_file(arg, files, 1);
		}
		dirlist = dirlist->next;
	}
	freelist(files, NULL);
}

void	do_ls_dir(t_opt arg, t_list *directory, int multidir)
{
	t_elem	*dirlist;

	dirlist = NULL;
	while (directory)
	{
		elemgetfiles(&dirlist, directory->content, "", arg);
		directory = directory->next;
	}
	dirlist = sort_elem(dirlist, arg);
	do_ls_dir2(arg, dirlist, multidir);
	freelist(dirlist, NULL);
}

void	do_ls_file(t_opt arg, t_list *path)
{
	t_list	*cur;
	t_elem	*files;

	cur = path;
	files = NULL;
	arg.a = 1;
	while (cur)
	{
		elemgetfiles(&files, cur->content, "", arg);
		cur = cur->next;
	}
	if (files)
		display_file(arg, files, 0);
	freelist(files, NULL);
}

void	core(t_opt arg, t_list *path, int multidir)
{
	DIR		*dir;
	t_list	*file;
	t_list	*directory;

	file = NULL;
	directory = NULL;
	while (path)
	{
		if ((dir = opendir(path->content)) == NULL)
			errno != ENOTDIR ? basicerror("ft_ls: ", path->content, 0) : \
					ft_lstpushback(&file, path->content, path->content_size);
		else
		{
			ft_lstpushback(&directory, path->content, path->content_size);
			if (closedir(dir) == -1)
				basicerror("ft_ls: ", path->content, 0);
		}
		path = path->next;
	}
	file ? do_ls_file(arg, file) : NULL;
	file && directory ? ft_putchar('\n') : NULL;
	directory ? do_ls_dir(arg, directory, multidir) : NULL;
	freelist(NULL, file);
	freelist(NULL, directory);
}
