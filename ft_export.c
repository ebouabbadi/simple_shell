/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:50:58 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_to_env(char *variable, char *valleur, t_env **envs)
{
	t_env	*lst;

	lst = (t_env *)ft_malloc(sizeof(t_env), 1);
	lst->name = variable;
	lst->vallue = valleur;
	lst->next = NULL;
	add_to_list_env(lst, envs);
}

int	if_variable_exist(char *variable, char *valleur, int flag, int append)
{
	t_env	*lst;

	lst = *g_global.envs;
	while (lst)
	{
		if (ft_strcmp(lst->name, variable) == 0)
		{
			if (append == 1)
			{
				if (!lst->vallue)
					lst->vallue = my_ft_strdup("");
				lst->vallue = my_ft_strjoin(lst->vallue, valleur, 1, 1);
			}
			else if (valleur)
			{
				if (flag)
					free(lst->vallue);
				lst->vallue = valleur;
			}
			return (free(variable), (1));
		}
		lst = lst->next;
	}
	return (0);
}

void	search_for_var_and_val(char **var, char **value, char *cmd, int *apnd)
{
	*value = NULL;
	if (find_value1(cmd))
	{
		*value = find_value1(cmd);
		*var = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(*value) - 2);
		*apnd = 1;
	}
	else if (find_value2(cmd))
	{
		*value = find_value2(cmd);
		*var = ft_substr(cmd, 0, ft_strlen(cmd) - ft_strlen(*value) - 1);
		*apnd = 0;
	}
	else
		*var = my_ft_strdup(cmd);
}

void	export_handler(t_mini *lst, int append, char *variable, char *value)
{
	if (lst->size == 1)
	{
		if (if_variable_exist(variable, value, 1, append) == 1)
			;
		else
			add_to_env(variable, value, g_global.envs);
	}
	else
	{
		free(variable);
		free(value);
	}
}

void	ft_export(t_mini *lst)
{
	int		append;
	int		i;
	char	*value;
	char	*variable;

	append = 0;
	i = 1;
	g_global.exit_status = 0;
	while (lst->cmd[i])
	{
		search_for_var_and_val(&variable, &value, lst->cmd[i], &append);
		if (variable[0] == '\0' || if_not_a_valid_identifier(variable) == 0
			|| ft_isdigit(variable[0]))
		{
			free(variable);
			free(value);
			msg_error_exprt_unst(lst->cmd[i], "export");
		}
		else
			export_handler(lst, append, variable, value);
		i++;
	}
}
