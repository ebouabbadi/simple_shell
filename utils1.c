/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:27:39 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elt;

	elt = (t_list *)ft_malloc(sizeof(*elt), 1);
	if (!elt)
		return (NULL);
	elt->content = content;
	elt->next = NULL;
	return (elt);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	lst_add_big_stack(t_mini **big_stack, t_list **stack)
{
	t_mini	*node;
	t_mini	*lst;

	lst = (t_mini *)ft_malloc(sizeof(t_mini), 1);
	lst->next = NULL;
	lst->stack = stack;
	if (*big_stack == NULL)
		*big_stack = lst;
	else
	{
		node = *big_stack;
		while (node->next)
			node = node->next;
		node->next = lst;
	}
}
