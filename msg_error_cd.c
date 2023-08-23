/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:55:44 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	msg_error_cd(char *msg)
{
	ft_putstr_fd("minishell : cd: ", 2);
	ft_putstr_fd(msg, 2);
	perror(" ");
}

void	msg_perror(char *str, int case_)
{
	if (case_ == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		perror(" ");
		exit(1);
	}
	else if (case_ == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		perror(" ");
	}
}
