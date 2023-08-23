/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:43:11 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shlvl_it_contains_alpha(t_env *tmp)
{
	int	minlvl;

	if (if_number(tmp->vallue) == 0)
	{
		free(tmp->vallue);
		tmp->vallue = ft_itoa(1);
	}
	else
	{
		minlvl = ft_atoi(tmp->vallue);
		if (minlvl < 0)
			minlvl = 0;
		else
			minlvl++;
		free(tmp->vallue);
		tmp->vallue = ft_itoa(minlvl);
	}
}

void	modify_shlvl_util(t_env **envs)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "SHLVL") == 0 && tmp->vallue)
			shlvl_it_contains_alpha(tmp);
		else if (ft_strcmp(tmp->name, "SHLVL") == 0 && !tmp->vallue)
		{
			free(tmp->vallue);
			tmp->vallue = ft_itoa(1);
		}
		tmp = tmp->next;
	}
}

void	modify_shlvl(t_env **envs)
{
	char	*str;

	str = search_in_env(envs, "SHLVL");
	if (str)
		modify_shlvl_util(envs);
	else
		creat_env(envs, my_ft_strdup("SHLVL"), ft_itoa(1));
}

void	env_handling(char **envp, t_env **stack, int i)
{
	int		size;
	char	*str;

	while (envp[++i])
	{
		size = 0;
		while (envp[i][size] != '=')
			size++;
		str = ft_substr(envp[i], 0, size);
		if (ft_strcmp(str, "OLDPWD") == 0)
		{
			free(str);
			continue ;
		}
		if (ft_strcmp(str, "PWD") == 0)
			creat_env(stack, str, getcwd(NULL, 0));
		else
			creat_env(stack, str, my_ft_strdup(ft_strrchr(envp[i], '=') + 1));
	}
}

t_env	**ft_env(char **envp)
{
	int		i;
	t_env	**stack;

	g_global.trash = (t_trash **)malloc(sizeof(t_trash *));
	if (!(g_global.trash))
		exit(1);
	*g_global.trash = NULL;
	stack = (t_env **)ft_malloc(sizeof(t_env *), 1);
	*stack = NULL;
	i = -1;
	env_handling(envp, stack, -1);
	modify_shlvl(stack);
	if (!search_in_env(stack, "PWD"))
		add_to_env(my_ft_strdup("PWD"), getcwd(NULL, 0), stack);
	return (stack);
}
