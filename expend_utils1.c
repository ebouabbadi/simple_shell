/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:18:21 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_add1(t_list **new_stack, t_list *lst)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(lst->content));
	node->dq = lst->dq;
	node->sq = lst->sq;
	node->expend = lst->expend;
	node->token = lst->token;
	ft_lstadd_back(new_stack, node);
}

void	ft_add2(t_list **new_stack, char *str, int token, int flag)
{
	t_list	*tmp;

	tmp = ft_lstnew(str);
	tmp->token = token;
	tmp->if_expend = flag;
	ft_lstadd_back(new_stack, tmp);
}

char	*expend_sq_dq_b(char *mot, char *str, int *i, int start)
{
	int		len;
	char	*var;
	char	*src;

	(*i)++;
	len = 0;
	start = *i;
	while (str[*i] && !verification2(str[(*i) + 1]))
	{
		len++;
		(*i)++;
	}
	var = ft_substr(str, start, len + 1);
	if (!search_in_env(g_global.envs, var))
		;
	else
	{
		src = ft_strdup(search_in_env(g_global.envs, var));
		mot = my_ft_strjoin(mot, src, 1, 1);
	}
	free(var);
	return (mot);
}

char	*expend_sq_dq_a(char *mot, char *str, int *i, int start)
{
	if (str[*i] == '$' && (str[(*i) + 1] == '?'))
	{
		mot = my_ft_strjoin(mot, ft_itoa(g_global.exit_status), 1, 1);
		(*i)++;
	}
	else if (str[*i] == '$' && verification2(str[(*i) + 1]))
		mot = my_ft_strjoin(mot, ft_strdup("$"), 1, 1);
	if (str[*i] == '$' && !verification2(str[(*i) + 1]))
		mot = expend_sq_dq_b(mot, str, i, start);
	return ((*i)++, mot);
}

char	*expend_sq_dq(t_list *node)
{
	char	*mot;
	int		i;
	int		len;
	int		start;

	i = 0;
	mot = ft_strdup("");
	while (node->content[i])
	{
		start = i;
		len = 0;
		while (node->content[i] && node->content[i] != '$')
		{
			len++;
			i++;
		}
		mot = my_ft_strjoin(mot, ft_substr(node->content, start, len), 1, 1);
		mot = expend_sq_dq_a(mot, node->content, &i, start);
	}
	return (mot);
}
