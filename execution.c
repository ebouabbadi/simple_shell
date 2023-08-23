/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:28:44 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	child_execu(t_mini *lst, t_env **envs)
{
	pipe_control(lst);
	if (lst->cmd[0])
		check_if_cmd_builtins_and_run_intside(lst, envs);
	if (lst->if_exit == 1)
	{
		if (g_global.prinf_old_pwd)
			ft_putendl_fd(g_global.msg_old_pwd, 1);
		exit(g_global.exit_status);
	}
	else
	{
		if (!lst->path)
			exit(g_global.exit_status);
		execve(lst->path, lst->cmd, lst->envp);
		msg_perror("exceve", 1);
	}
}

void	exec_cmds(t_mini *lst, t_env **envs)
{
	if (lst->cmd[0])
		check_if_cmd_builtins_and_run_outside(lst, envs);
	if (lst->cmd[0] && (if_cmd_in_builtins(lst) == 0))
		searching_for_cmd(lst);
	g_global.if_fork = 1;
	signal(SIGQUIT, fanc_aplic);
	g_global.pid = fork();
	if (g_global.pid < 0)
		msg_perror("fork", 1);
	if (g_global.pid == 0)
		child_execu(lst, envs);
	close_pipe_in_main_process(lst);
	wait_and_return_value_of_waitpid(lst);
}

int	handling_redirections_and_init_lst(t_mini **big_stack)
{
	t_mini	*lst;
	int		i;

	i = 0;
	lst = *(big_stack);
	while (lst)
	{
		lst->file_heredoc = my_ft_strjoin("/tmp/trash", ft_itoa(i++), 0, 1);
		lst->if_exit = 0;
		lst->std_out = 1;
		lst->std_in = 0;
		lst->f_read = -1;
		lst->f_write = -1;
		lst->size = lst_size(big_stack);
		if (redirections(lst) == -1)
			return (ft_unlink(big_stack), -1);
		lst = lst->next;
	}
	return (0);
}

int	execution(t_mini **big_stack, t_env **envs)
{
	t_mini	*lst;

	lst = *big_stack;
	if (-1 == handling_redirections_and_init_lst(big_stack))
		return (1);
	while (lst)
	{
		if (lst->next)
			ft_pipe(lst);
		lst->envs = envs;
		lst->envp = extract_env(envs);
		exec_cmds(lst, envs);
		free(lst->cmd);
		free_tab(lst->envp);
		free(lst->path);
		lst = lst->next;
	}
	ft_unlink(big_stack);
	return (0);
}
