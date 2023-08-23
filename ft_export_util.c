/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:49:01 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	if_not_a_valid_identifier(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (!ft_isalpha(variable[i])
			&& !ft_isdigit(variable[i]) && variable[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*find_value1(char *cmd)
{
	int	i;
	int	start;
	int	len;

	len = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
		{
			i += 2;
			start = i;
			if (!cmd[i])
				return (my_ft_strdup(""));
			while (cmd[i])
			{
				len++;
				i++;
			}
			return (ft_substr(cmd, start, len));
		}
		i++;
	}
	return (NULL);
}

char	*find_value2(char *cmd)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			i++;
			start = i;
			if (!cmd[i])
				return (my_ft_strdup(""));
			while (cmd[i])
			{
				len++;
				i++;
			}
			return (my_ft_substr(cmd, start, len));
		}
		i++;
	}
	return (NULL);
}
