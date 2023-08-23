/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:31:19 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_pipe(t_mini *lst)
{
	int	fd[2];

	pipe(fd);
	lst->std_out = fd[1];
	lst->next->std_in = fd[0];
}

void	pipe_control_2(t_mini *lst)
{
	if (lst->f_write != -1)
	{
		if (lst->std_out != 1)
			if (close(lst->std_out) == -1)
				msg_perror("close3", 1);
		if (dup2(lst->f_write, 1) == -1)
			msg_perror("dup2", 1);
	}
	if (lst->f_read != -1)
	{
		if (lst->std_in != 0)
			if (close(lst->std_in) == -1)
				msg_perror("close4", 1);
		if (dup2(lst->f_read, 0) == -1)
			msg_perror("dup2", 1);
	}
}

void	pipe_control(t_mini *lst)
{
	if (lst->std_out != 1)
	{
		if (close(lst->next->std_in) == -1)
			msg_perror("dup2", 1);
		if (dup2(lst->std_out, 1) == -1)
			msg_perror("close1", 1);
	}
	if (lst->std_in != 0)
	{
		if (dup2(lst->std_in, 0) == -1)
			msg_perror("dup2", 1);
	}
	pipe_control_2(lst);
}

void	close_pipe_in_main_process(t_mini *lst)
{
	if (lst->std_out != 1)
		close(lst->std_out);
	if (lst->std_in != 0)
		close(lst->std_in);
}
