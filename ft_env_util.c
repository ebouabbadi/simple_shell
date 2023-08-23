/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:43:00 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_to_list_env(t_env *lst, t_env **env)
{
	t_env	*node;

	node = *env;
	if (!*env)
	{
		(*env) = lst;
		return ;
	}
	while (node)
	{
		if (!node->next)
		{
			node->next = lst;
			break ;
		}
		node = node->next;
	}
}

void	affich_env(t_env **stack)
{
	t_env	*lst;

	lst = *stack;
	while (lst)
	{
		if (lst->vallue)
			printf("%s=%s\n", lst->name, lst->vallue);
		lst = lst->next;
	}
	g_global.exit_status = 0;
}

int	if_number(char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (ft_isdigit(val[i]) == 0)
		{
			if ((val[i] == '+' && i == 0) || (val[i] == '-' && i == 0))
			{
				i++;
				continue ;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

void	creat_env(t_env **stack, char *name, char *val)
{
	t_env	*lst;

	lst = (t_env *)ft_malloc(sizeof(t_env), 1);
	lst->next = NULL;
	lst->name = name;
	lst->vallue = val;
	add_to_list_env(lst, stack);
}
