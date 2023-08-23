/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:40:16 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	echo_with_flag_minus(t_mini *lst, int *flag, int *i)
{
	int	j;

	while (lst->cmd[*i])
	{
		j = 1;
		if (lst->cmd[*i][0] != '-')
			return ;
		while (lst->cmd[*i][j])
		{
			if (lst->cmd[*i][j] != 'n')
				return ;
			j++;
		}
		*flag = 1;
		(*i)++;
	}
}

void	ft_echo(t_mini *lst)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	echo_with_flag_minus(lst, &flag, &i);
	while (lst->cmd[i])
	{
		ft_putstr_fd(lst->cmd[i], 1);
		i++;
		if (lst->cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		printf("\n");
}
