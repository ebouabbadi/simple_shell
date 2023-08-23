/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affich_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:46:56 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_strlen_lst(t_env **envs)
{
	t_env *lst;
	int i;

	lst = *envs;
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void sort_env(char **tab)
{
	char *str;
	int i;

	i = 0;
	while (tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			str = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = str;
			i = -1;
		}
		i++;
	}
}

void ft_affich(t_env **envs, char **tab)
{
	char *vallu;
	int i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s", tab[i]);
		vallu = search_in_env(envs, tab[i]);
		if (vallu)
			printf("=\"%s\"", vallu);
		printf("\n");
		i++;
	}
}

void affich_export(t_env **envs)
{
	int i;
	t_env *lst;
	char **tab;

	i = 0;
	tab = ft_malloc(sizeof(char *), (ft_strlen_lst(envs) + 1));
	lst = *envs;
	while (lst)
	{
		tab[i] = my_ft_strdup(lst->name);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	sort_env(tab);
	ft_affich(envs, tab);
	free_tab(tab);
	g_global.exit_status = 0;
}
