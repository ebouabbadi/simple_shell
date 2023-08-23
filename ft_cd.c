/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:36:30 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	if_cd_and_minus(t_env **envs, int size, int *flag)
{
	char	*value;
	DIR		*dir;

	value = search_in_env(envs, "OLDPWD");
	dir = opendir(value);
	if (!value)
	{
		g_global.exit_status = 1;
		*flag = 0;
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	}
	else if (!value[0])
		if_cd_and_minus2();
	else if (value && value[0] && (dir == NULL))
	{
		g_global.exit_status = 1;
		msg_error_cd(value);
		*flag = 0;
	}
	else
		if_cd_and_minus3(size);
	if (dir)
		closedir(dir);
}

void	if_cd_and_argument(char **cmd, int size, int *flag)
{
	DIR		*dir;

	dir = opendir(cmd[1]);
	if (dir == NULL)
	{
		msg_error_cd(cmd[1]);
		g_global.exit_status = 1;
		*flag = 0;
	}
	else
		if_cd_and_argument2(cmd, size, flag);
	if (dir)
		closedir(dir);
}

void	if_cd_only(t_env **envs, int size, int *flag)
{
	DIR		*dir;
	char	*str;

	str = search_in_env(envs, "HOME");
	dir = opendir(str);
	if (!str)
		home_not_set();
	else if (str[0] == '\0')
	{
		g_global.exit_status = 0;
		if (size != 1)
			*flag = 0;
	}
	else if (dir == NULL)
	{
		g_global.exit_status = 1;
		msg_error_cd(str);
		*flag = 0;
	}
	else
		if_cd_only2(size, str);
	if (dir)
		closedir(dir);
}

void	ft_cd(t_env **envs, char **cmd, int size)
{
	int		flag;

	flag = 1;
	g_global.prinf_old_pwd = 0;
	if (cmd[1] && ft_strcmp(cmd[1], "-") == 0)
		if_cd_and_minus(envs, size, &flag);
	else if (cmd[1] && ft_strcmp(cmd[1], "~") && ft_strcmp(cmd[1], "--") != 0)
		if_cd_and_argument(cmd, size, &flag);
	else
		if_cd_only(envs, size, &flag);
	if (flag == 1)
	{
		if (!search_in_env(envs, "OLDPWD"))
			add_to_env(my_ft_strdup("OLDPWD"),
				my_ft_strdup(g_global.pwd), envs);
		else
			modif_oldpwd_in_env(envs);
		modif_pwd_in_env(envs);
	}
	g_global.old_pwd = g_global.pwd;
}
