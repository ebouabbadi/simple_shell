/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error_export_unset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:56:14 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	msg_error_exprt_unst(char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
	g_global.exit_status = 1;
}
