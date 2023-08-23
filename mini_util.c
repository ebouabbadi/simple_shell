/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:54:16 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	char	ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (*(char *)dst);
}

char	*my_ft_strjoin(char const *s1, char const *s2, int flag1, int flag2)
{
	char	*d;
	char	*s;
	char	*st;

	if (!s1 || !s2)
	{
		if (flag1)
			free((char *)s1);
		if (flag2)
			free((char *)s2);
		return (NULL);
	}
	d = (char *)s1;
	s = (char *)s2;
	st = (char *)ft_malloc(sizeof(char), (ft_strlen(s) + ft_strlen(d) + 1));
	if (!st)
		return (NULL);
	*st = 0;
	ft_strcat(st, d);
	ft_strcat(st, s);
	if (flag1)
		free(d);
	if (flag2)
		free(s);
	return (st);
}

void	*ft_malloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(size * count);
	if (!p)
	{
		ft_putendl_fd("Error: malloc!!", 2);
		exit(1);
	}
	ft_bzero(p, (count * size));
	add_to_trash(p);
	return (p);
}
