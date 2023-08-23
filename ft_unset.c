/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:52:45 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_envaironment2(t_env **envs, char *namee, int x)
{
	t_env	*lst;
	t_env	*swp;

	lst = *envs;
	while (lst->next)
	{
		if (ft_strcmp((lst->next)->name, namee) == 0)
		{
			x = 1;
			swp = lst->next->next;
			free(lst->next->name);
			free(lst->next->vallue);
			free(lst->next);
			lst->next = NULL;
			break ;
		}
		lst = lst->next;
	}
	if (x == 1)
		add_to_list_env(swp, envs);
}

void	delete_envaironment(t_env **envs, char *namee)
{
	t_env	*lst;

	lst = *envs;
	if (ft_strcmp(lst->name, namee) == 0)
	{
		*envs = lst->next;
		free(lst->vallue);
		free(lst->name);
		free(lst);
		return ;
	}
	delete_envaironment2(envs, namee, 0);
}

void	ft_unset(t_env **envs, t_mini *lst)
{
	int	i;

	i = 1;
	if (*envs == NULL)
		return ;
	while (lst->cmd[i])
	{
		if ((ft_isdigit(lst->cmd[i][0]) == 1)
			|| if_not_a_valid_identifier(lst->cmd[i]) == 0)
		{
			msg_error_exprt_unst(lst->cmd[i], "unset");
			i++;
			continue ;
		}
		if (lst->size == 1)
			delete_envaironment(envs, lst->cmd[i]);
		i++;
	}
}
