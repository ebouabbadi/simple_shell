/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:35:08 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*search_in_env(t_env **envs, char *variable)
{
	t_env	*lst;

	lst = *envs;
	while (lst)
	{
		if (ft_strcmp(lst->name, variable) == 0)
			return (lst->vallue);
		lst = lst->next;
	}
	return (NULL);
}

void	modif_pwd_in_env(t_env **envs)
{
	t_env	*lst;

	lst = *envs;
	while (lst)
	{
		if ((ft_strcmp(lst->name, "PWD") == 0))
		{
			free(lst->vallue);
			lst->vallue = getcwd(NULL, 0);
			return ;
		}
		lst = lst->next;
	}
}

void	modif_oldpwd_in_env(t_env **envs)
{
	char	*s;
	t_env	*tmp;

	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			s = tmp->vallue;
			tmp->vallue = my_ft_strdup(g_global.pwd);
			add_to_trash(s);
			break ;
		}
		tmp = tmp->next;
	}
}

void	home_not_set(void)
{
	g_global.exit_status = 1;
	ft_putendl_fd("minishell: cd: HOME not set", 2);
}
