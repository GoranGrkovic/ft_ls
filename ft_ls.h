/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 19:54:48 by gogrkovi          #+#    #+#             */
/*   Updated: 2019/10/10 14:19:40 by gogrkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <uuid/uuid.h>

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

typedef struct		s_opt
{
	int				l;
	int				upper_r;
	int				a;
	int				r;
	int				t;
	int				u;
	int				f;
	int				g;
}					t_opt;

typedef struct		s_elem
{
	char			*name;
	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_size
{
	int				total;
	int				size;
	int				groupspace;
	int				userspace;
	int				linkspace;
	int				min;
	int				maj;
}					t_size;

void				freelist(t_elem *elem, t_list *list);
int					one_of(char c, char *str);

void				error_arg(char arg);
void				basicerror(char *name, char *error, int ex);

void				core(t_opt arg, t_list *path, int multidir);
void				display_file(t_opt arg, t_elem *files, int fileordir);

int					elemget(t_elem **files, struct dirent *file, char *path, \
		t_opt arg);
void				elemgetfiles(t_elem **files, char *name, char *path, \
		t_opt arg);

void				display_date(time_t date);

t_elem				*sort_elem(t_elem *list, t_opt arg);
void				sort(t_elem **list, int (*cmp)());
t_elem				*reversesort(t_elem *list);

int					cmp_alpha(t_elem *elem1, t_elem *elem2);
int					cmp_time(t_elem *elem1, t_elem *elem2);

void				recursion(t_opt arg, t_elem *files);

void				ls_simple(t_opt arg, t_elem *files);
void				ls_long(t_opt arg, t_elem *files, int fileordir);

t_size				get_size(t_opt arg, t_elem *files);

void				print_access(t_elem *elem);
void				print_int(int nlink, int spacemax);
void				print_str(char *str, int spacemax);
void				print_majmin(t_elem *file, t_size size);
void				freelist(t_elem *elem, t_list *list);

#endif
