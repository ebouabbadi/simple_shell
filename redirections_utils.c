/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 07:00:21 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	command_make(t_mini *lst, int len)
{
	t_list	*node;

	lst->cmd = ft_malloc(sizeof(char *), (len + 1));
	add_to_trash(lst->cmd);
	node = *(lst->stack);
	len = 0;
	while (node)
	{
		if (node->if_add == 1)
		{
			lst->cmd[len] = node->content;
			len++;
		}
		node = node->next;
	}
	lst->cmd[len] = NULL;
}

int	verification33(char c)
{
	if (c == '#' || c == '%' || c == '*' || c == '+'
		|| c == ',' || c == ' ' || c == '-' || c == '.'
		|| c == '/' || c == ':' || c == '=' || c == '$'
		|| c == '?' || c == '@' || c == ']' || c == '['
		|| c == '^' || c == '}' || c == '{' || c == '~'
		|| c == '\'' || c == '\"' || c == '\0')
		return (1);
	return (0);
}

void	expend_and_write_in_fd(char *inpt, int *i, int fd)
{
	int		start;
	char	*str;

	if (inpt[(*i)] == '$' && inpt[(*i) + 1] == '?')
	{
		str = ft_itoa(g_global.exit_status);
		ft_putstr_fd(str, fd);
		free(str);
		(*i) += 2;
	}
	else if (inpt[(*i)] && verification33(inpt[(*i) + 1]) == 1)
	{
		ft_putstr_fd("$", fd);
		(*i)++;
	}
	else
	{
		(*i)++;
		start = (*i);
		while (!verification33(inpt[(*i)]))
			(*i)++;
			str = ft_substr(inpt, start, (*i) - start);
		ft_putstr_fd(search_in_env(g_global.envs, str), fd);
		free(str);
	}
}

void	expend_inside_herdoc(int fd, char *inpt)
{
	int		i;
	int		start;
	int		len;
	char	*str;

	i = 0;
	while (inpt[i])
	{
		start = i;
		len = 0;
		while (inpt[i] != '\0' && inpt[i] != '$')
		{
			len++;
			i++;
		}
		if (len)
		{
			str = ft_substr(inpt, start, len);
			ft_putstr_fd(str, fd);
			free(str);
		}
		expend_and_write_in_fd(inpt, &i, fd);
	}
	ft_putstr_fd("\n", fd);
}
