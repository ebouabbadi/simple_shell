/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:22:55 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	lst_size(t_mini **stack)
{
	int		i;
	t_mini	*lst;

	i = 0;
	lst = *stack;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	if_number2(char *val)
{
	int	i;

	i = 0;
	if (val[0] == '\0')
		return (0);
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

int	len__(t_env **envs)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = *envs;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
