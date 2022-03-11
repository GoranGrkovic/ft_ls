/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gogrkovi <gogrkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 06:31:31 by gogrkovi          #+#    #+#             */
/*   Updated: 2019/10/02 18:04:53 by gogrkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*c;
	int		len;

	len = -1;
	while (s1[++len])
		;
	c = (char *)malloc(len * sizeof(char) + 1);
	if (c != NULL)
		ft_strcpy(c, s1);
	*(c + len) = '\0';
	return (c);
}
