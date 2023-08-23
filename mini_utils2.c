/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:19:07 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*my_ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = (char *)ft_malloc(sizeof(char), (len + 1));
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*my_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = (char *) ft_malloc(sizeof(char), (len + 1));
	while (start < ft_strlen(s) && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	add_to_trash(str);
	return (str);
}

void	add_to_trash_utul(void)
{
	ft_putendl_fd("Error: malloc!!", 2);
	exit(1);
}

void	add_to_trash(void *ptr)
{
	t_trash	*trs;
	t_trash	*node;

	trs = malloc(sizeof(t_trash));
	if (!trs)
		add_to_trash_utul();
	trs->next = NULL;
	trs->p = ptr;
	node = *(g_global.trash);
	if (!*g_global.trash)
	{
		(*g_global.trash) = trs;
		return ;
	}
	while (node)
	{
		if (!node->next)
		{
			node->next = trs;
			break ;
		}
		node = node->next;
	}
}
