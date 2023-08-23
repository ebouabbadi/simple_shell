/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:25:02 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**extract_env(t_env **envs)
{
	char	**env;
	t_env	*lst;
	int		i;

	i = 0;
	env = ft_malloc(sizeof(char *), (len__(envs) + 1));
	lst = *envs;
	while (lst)
	{
		env[i] = ft_strjoin(lst->name, "=");
		env[i] = my_ft_strjoin(env[i], lst->vallue, 1, 0);
		i++;
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}

char	*to_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*comd_existe(t_mini *lst)
{
	char	*add_backslash;
	char	*path;
	char	**tab_path;
	char	*str;
	int		i;

	i = 0;
	str = to_path(lst->envp);
	if (!str)
		return (NULL);
	tab_path = ft_split(str, ':');
	while (tab_path[i])
	{
		add_backslash = ft_strjoin(tab_path[i], "/");
		path = my_ft_strjoin(add_backslash, lst->cmd[0], 1, 0);
		if (access(path, F_OK) == 0)
			return (free_tab(tab_path), (path));
		free(path);
		i++;
	}
	return (free_tab(tab_path), (NULL));
}

int	if_cmd_in_builtins(t_mini *lst)
{
	if (ft_strcmp(lst->cmd[0], "unset") == 0
		|| ft_strcmp(lst->cmd[0], "export") == 0
		|| ft_strcmp(lst->cmd[0], "echo") == 0
		|| ft_strcmp(lst->cmd[0], "pwd") == 0
		|| ft_strcmp(lst->cmd[0], "env") == 0
		|| ft_strcmp(lst->cmd[0], "exit") == 0
		|| ft_strcmp(lst->cmd[0], "cd") == 0)
		return (1);
	return (0);
}

void	ft_unlink(t_mini **big_stack)
{
	t_mini	*lst;

	lst = *(big_stack);
	while (lst)
	{
		lst = *big_stack;
		while (lst)
		{
			unlink(lst->file_heredoc);
			free(lst->file_heredoc);
			lst = lst->next;
		}
	}
}
