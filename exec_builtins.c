/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:20:20 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_if_cmd_builtins_and_run_outside(t_mini *lst, t_env **envs)
{
	if ((ft_strcmp(lst->cmd[0], "cd") == 0))
	{
		ft_cd(envs, lst->cmd, lst->size);
		lst->if_exit = 1;
	}
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
	{
		ft_exit(lst);
	}
	else if ((ft_strcmp(lst->cmd[0], "export") == 0) && lst->cmd[1])
	{
		ft_export(lst);
		lst->if_exit = 1;
	}
	else if ((ft_strcmp(lst->cmd[0], "unset") == 0))
	{
		ft_unset(envs, lst);
		lst->if_exit = 1;
	}
}

void	check_if_cmd_builtins_and_run_intside(t_mini *lst, t_env **envs)
{
	if (ft_strcmp(lst->cmd[0], "env") == 0)
	{
		affich_env(envs);
		lst->if_exit = 1;
	}
	else if ((ft_strcmp(lst->cmd[0], "export") == 0) && !lst->cmd[1])
	{
		affich_export(envs);
		lst->if_exit = 1;
	}
	else if ((ft_strcmp(lst->cmd[0], "echo") == 0))
	{
		ft_echo(lst);
		g_global.exit_status = 0;
		lst->if_exit = 1;
	}
	else if ((ft_strcmp(lst->cmd[0], "pwd") == 0))
	{
		ft_pwd();
		lst->if_exit = 1;
	}
}
