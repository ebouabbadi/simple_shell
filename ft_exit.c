/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:45:17 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_exit_1(t_mini *lst)
{
	if (!lst->cmd[2])
	{
		if (lst->size == 1)
			exit(ft_atoi(lst->cmd[1]));
		else
			lst->if_exit = 1;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("exit", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		lst->if_exit = 1;
		g_global.exit_status = 1;
	}
}

void	ft_exit_2(t_mini *lst)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit", 2);
	ft_putstr_fd(lst->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (lst->size == 1)
		exit(255);
	else
		lst->if_exit = 1;
}

void	ft_exit(t_mini *lst)
{
	if (lst->size == 1)
		ft_putstr_fd("exit\n", 2);
	if (lst->cmd[1])
	{
		if (if_number2(lst->cmd[1]))
			ft_exit_1(lst);
		else
			ft_exit_2(lst);
	}
	else
	{
		if (lst->size == 1)
			exit(g_global.exit_status);
		else
			lst->if_exit = 1;
	}
}
