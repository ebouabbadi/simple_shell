/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:55:21 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	syntax_error2(t_list **stack, t_list *lst)
{
	lst = *stack;
	while (lst)
	{
		if ((lst->token == T_REDOUT || lst->token == T_HEREDOC
				|| lst->token == T_REDINP
				|| lst->token == T_REDAPND) && !lst->next)
			return (1);
		else if ((lst->token == T_REDOUT || lst->token == T_HEREDOC
				|| lst->token == T_REDINP
				|| lst->token == T_REDAPND) && lst->next->token == T_SPACE)
		{
			lst = lst->next->next;
			if (!lst)
				return (1);
			else if (lst->token != T_MOT)
				return (1);
			continue ;
		}
		else if ((lst->token == T_REDOUT || lst->token == T_HEREDOC
				|| lst->token == T_REDINP
				|| lst->token == T_REDAPND) && (lst->next->token != T_MOT))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	syntax_error(t_list **stack)
{
	t_list	*lst;

	lst = *stack;
	if (lst->token == T_PIPE || syntax_error2(stack, lst))
		return (1);
	while (lst)
	{
		if (lst->token == T_PIPE && !lst->next)
			return (1);
		else if (lst->token == T_PIPE && lst->next->token == T_SPACE)
		{
			lst = lst->next->next;
			if (!lst)
				return (1);
			else if (lst->token == T_PIPE)
				return (1);
		}
		else if (lst->token == T_PIPE && lst->next->token == T_PIPE)
			return (1);
		lst = lst->next;
	}
	return (0);
}
