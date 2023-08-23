/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:50:08 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	tokenization(t_list **stack)
{
	t_list	*lst;

	lst = *stack;
	while (lst)
	{
		if (lst->content[0] == ' ')
			lst->token = T_SPACE;
		else if (!ft_strcmp(lst->content, ">>"))
			lst->token = T_REDAPND;
		else if (!ft_strcmp(lst->content, "<<"))
			lst->token = T_HEREDOC;
		else if (!ft_strcmp(lst->content, ">"))
			lst->token = T_REDOUT;
		else if (!ft_strcmp(lst->content, "<"))
			lst->token = T_REDINP;
		else if (!ft_strcmp(lst->content, "|"))
			lst->token = T_PIPE;
		else
			lst->token = T_MOT;
		lst = lst->next;
	}
}
