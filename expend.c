/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:41:45 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	expend_mot_simple1(int i, t_list **new_stack, t_list *node, int start)
{
	int	len;

	len = 0;
	while (node->content[i] && node->content[i] != '$')
	{
		len++;
		i++;
	}
	if (len != 0)
		ft_add2(new_stack, ft_substr(node->content, start, len), T_MOT, 0);
	if (node->content[i] == '$' && (node->content[i + 1] == '?'))
	{
		ft_add2(new_stack, ft_itoa(g_global.exit_status), T_MOT, 0);
		i++;
	}
	else if (node->content[i] == '$' && verification2(node->content[i + 1]))
	{
		if (!node->next || !(node->content[i + 1] == '\0'))
			ft_add2(new_stack, ft_strdup("$"), T_MOT, 0);
		else if (node->next->token != T_MOT)
			ft_add2(new_stack, ft_strdup("$"), T_MOT, 0);
	}
	return (i);
}

int	expend_mot_simple3(int i, t_list **new_stack, char *val)
{
	int		k;
	char	**tab;

	if (val[0] == ' ')
		ft_add2(new_stack, ft_strdup(" "), T_SPACE, 0);
	tab = ft_split(val, ' ');
	k = 0;
	while (tab[k])
	{
		ft_add2(new_stack, ft_strdup(tab[k]), T_MOT, 0);
		k++;
		if (tab[k])
			ft_add2(new_stack, ft_strdup(" "), T_SPACE, 0);
	}
	free_tab(tab);
	if (val[ft_strlen(val) - 1] == ' ')
		ft_add2(new_stack, ft_strdup(" "), T_SPACE, 0);
	return (i);
}

int	expend_mot_simple2(int i, t_list **new_stack, t_list *node, int start)
{
	int		len;
	char	*var;
	char	*val;

	len = 0;
	start = i;
	while (node->content[i] && !verification2(node->content[i + 1]))
	{
		len++;
		i++;
	}
	var = ft_substr(node->content, start, len + 1);
	val = search_in_env(g_global.envs, var);
	if (!val)
	{
		if (node->content[0] == '$' && !ft_strcmp(node->content + 1, var))
			ft_add2(new_stack, NULL, T_MOT, 0);
		else
			ft_add2(new_stack, ft_strdup(""), T_MOT, 0);
	}
	else
		i = expend_mot_simple3(i, new_stack, val);
	free(var);
	return (i);
}

void	expend_mot_simple(t_list *node, t_list **new_stack)
{
	int	i;
	int	start;

	i = 0;
	while (node->content[i])
	{
		start = i;
		i = expend_mot_simple1(i, new_stack, node, start);
		if (node->content[i] == '$' && !verification2(node->content[i + 1]))
		{
			i++;
			i = expend_mot_simple2(i, new_stack, node, start);
		}
		i++;
	}
}

void	expend(t_list **stack, t_list **new_stack)
{
	t_list	*lst;
	int		i;
	char	*str;

	i = 0;
	lst = *stack;
	mark_expend(stack);
	cancel_expend(stack);
	while (lst)
	{
		if (lst->expend == 1 && lst->sq == 0 && lst->dq == 1)
		{
			str = lst->content;
			lst->content = expend_sq_dq(lst);
			free(str);
			ft_add1(new_stack, lst);
		}
		else if (lst->expend == 1 && lst->sq == 0 && lst->dq == 0)
			expend_mot_simple(lst, new_stack);
		else
			ft_add1(new_stack, lst);
		lst = lst->next;
	}
}
