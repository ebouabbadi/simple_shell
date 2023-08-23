/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:39:14 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	if_cd_and_minus2(void)
{
	g_global.msg_old_pwd = search_in_env(g_global.envs, "OLDPWD");
	g_global.prinf_old_pwd = 1;
	g_global.exit_status = 0;
}

void	if_cd_and_minus3(int size)
{
	g_global.prinf_old_pwd = 1;
	g_global.exit_status = 0;
	g_global.msg_old_pwd = search_in_env(g_global.envs, "OLDPWD");
	if (size == 1)
	{
		if (-1 == chdir(g_global.old_pwd))
			msg_perror("chdir", 2);
	}
}

void	if_cd_and_argument2(char **cmd, int size, int *flag)
{
	char	*str;

	*flag = 0;
	str = getcwd(NULL, 0);
	if (!str && ft_strcmp(cmd[1], ".") == 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories:", 2);
		ft_putendl_fd("No such file or directory", 2);
	}
	g_global.exit_status = 0;
	if (size == 1)
	{
		*flag = 1;
		if (-1 == chdir(cmd[1]))
			msg_perror("chdir", 2);
	}
	if (str)
		free(str);
}

void	if_cd_only2(int size, char *str)
{
	g_global.exit_status = 0;
	if (size == 1)
		if (-1 == chdir(str))
			msg_perror("chdir", 2);
}
