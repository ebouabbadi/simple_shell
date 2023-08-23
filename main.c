/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:13:00 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

int	init_variable_global(int status)
{
	char	*pwd1;

	if (status)
	{
		g_global.exit_status = 0;
		rl_catch_signals = 0;
	}
	else
	{
		g_global.skip = 0;
		g_global.if_fork = 0;
		g_global.prinf_old_pwd = 0;
		pwd1 = getcwd(NULL, 0);
		if (pwd1)
		{
			free(g_global.pwd);
			g_global.pwd = pwd1;
		}
	}
	return (0);
}

char	*ft_readline(void)
{
	char	*line;

	signal(SIGINT, fanc_aplic);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = get_c;
	line = readline("minishell$ ");
	if (!line)
	{
		ft_putendl_fd("exit", 2);
		exit(g_global.exit_status);
	}
	if (!line[0] || g_global.skip == 1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	t_env	**envs;
	t_mini	**big_stack;
	char	*line;

	(void)av;
	if (ac != 1)
		exit(1);
	envs = ft_env(envp);
	g_global.pwd = my_ft_strdup("");
	init_variable_global(1);
	while (1)
	{
		init_variable_global(0);
		g_global.envs = envs;
		line = ft_readline();
		if (!line)
			continue ;
		add_history(line);
		big_stack = parsing(line);
		if (!big_stack)
			continue ;
		execution(big_stack, envs);
	}
}
