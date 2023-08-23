/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:45:46 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	cancel_expend(t_list **stack)
{
	t_list	*lst;

	lst = *stack;
	while (lst && lst->next)
	{
		if (lst->token == T_HEREDOC)
		{
			lst = lst->next;
			if (lst->token == T_SPACE)
				lst = lst->next;
			if (lst->expend == 1)
				lst->expend = 0;
		}
		lst = lst->next;
	}
}

void	mark_expend(t_list **stack)
{
	int		i;
	t_list	*lst;

	lst = *stack;
	while (lst)
	{
		i = 0;
		lst->expend = 0;
		lst->dq = 0;
		lst->sq = 0;
		if (lst->content[0] == D_QT)
			lst->dq = 1;
		if (lst->content[0] == S_QT)
			lst->sq = 1;
		while (lst->content[i])
		{
			if (lst->content[i] == '$')
				lst->expend = 1;
			i++;
		}
		lst = lst->next;
	}
}

int	verification2(char c)
{
	if (c == '#' || c == '%' || c == '*' || c == '+'
		|| c == ',' || c == ' ' || c == '-' || c == '.'
		|| c == '/' || c == ':' || c == '=' || c == '$'
		|| c == '?' || c == '@' || c == ']' || c == '['
		|| c == '^' || c == '}' || c == '{' || c == '~'
		|| c == INR || c == OUTR || c == '0' || c == D_QT
		|| c == S_QT || c == '\0')
		return (1);
	return (0);
}
