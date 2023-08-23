/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:32:45 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_and_print(char *line, char *line1)
{
	free(line);
	free(line1);
	ft_putendl_fd("minishell: Syntax Error", 2);
	g_global.exit_status = 1;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_stack(t_list **stack, int status)
{
	if (status == 0)
	{
		while (*stack)
		{
			if ((*stack)->token == T_MOT || (*stack)->token == T_SPACE)
				free((*stack)->content);
			free(*stack);
			*stack = (*stack)->next;
		}
	}
	else if (status == 1)
	{
		while (*stack)
		{
			if ((*stack)->content)
				free((*stack)->content);
			free(*stack);
			*stack = (*stack)->next;
		}
	}
	free(stack);
}

void	free_big_stack(t_mini **stk)
{
	t_mini	*lst;
	t_list	*node;

	lst = *stk;
	while (lst)
	{
		node = *(lst->stack);
		while (node)
		{
			free(node->content);
			free(node);
			node = node->next;
		}
		free(lst->stack);
		free(lst);
		lst = lst->next;
	}
	free(stk);
}
