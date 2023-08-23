/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_for_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:32:35 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	searching_for_cmd_util1(t_mini *lst)
{
	if (access(lst->cmd[0], X_OK | F_OK | R_OK | W_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->cmd[0], 2);
		perror(" ");
		lst->path = NULL;
		if (access(lst->cmd[0], F_OK))
			g_global.exit_status = 127;
		else
			g_global.exit_status = 126;
	}
	else
		lst->path = lst->cmd[0];
}

void	searching_for_cmd_util2(t_mini *lst)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(lst->cmd[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	lst->path = NULL;
	g_global.exit_status = 126;
}

void	searching_for_cmd_util3(t_mini *lst, struct stat var)
{
	lst->path = comd_existe(lst);
	if ((var.st_mode & S_IFMT) == S_IFREG)
		lst->path = my_ft_strdup(lst->cmd[0]);
	else if (!search_in_env(g_global.envs, "PATH"))
	{
		lst->path = NULL;
		g_global.exit_status = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (!lst->cmd[0][0] || ((var.st_mode & S_IFMT) == S_IFDIR)
		|| !lst->path)
	{
		if (lst->path)
			free(lst->path);
		lst->path = NULL;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_global.exit_status = 127;
	}
}

char	*searching_for_cmd(t_mini *lst)
{
	struct stat	var;
	DIR			*dir;

	dir = opendir(lst->cmd[0]);
	lstat(lst->cmd[0], &var);
	if (dir != NULL && ft_strchr(lst->cmd[0], '/'))
	{
		free(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->cmd[0], 2);
		ft_putstr_fd(" is a directory\n", 2);
		g_global.exit_status = 126;
		return (NULL);
	}
	else if (lst->cmd[0][0] == '.' && lst->cmd[0][1] == '/')
		searching_for_cmd_util1(lst);
	else if (0 == access(lst->cmd[0], F_OK | W_OK)
		&& ((var.st_mode & S_IFMT) != S_IFDIR))
		searching_for_cmd_util2(lst);
	else
		searching_for_cmd_util3(lst, var);
	if (dir)
		closedir(dir);
	return (NULL);
}
