/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:26:48 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*add_big_stack1(t_list **small_stack, t_list *lst)
{
	int		flag;
	char	*str;

	flag = 0;
	if (lst->token == T_SPACE)
		;
	else if (lst->token != T_MOT)
		ft_add1(small_stack, lst);
	else if (lst->token == T_MOT)
	{
		str = ft_strdup("");
		while (lst->token == T_MOT)
		{
			if (lst->sq == 1 || lst->dq == 1)
				flag = 1;
			str = my_ft_strjoin(str, lst->content, 1, 0);
			if (lst->next && lst->next->token == T_MOT)
				lst = lst->next;
			else
				break ;
		}
		ft_add2(small_stack, str, T_MOT, flag);
	}
	return (lst);
}

t_mini	**add_big_stack(t_list **stack)
{
	t_list	**small_stack;
	t_mini	**big_stack;
	t_list	*lst;

	lst = *stack;
	big_stack = (t_mini **)ft_malloc(sizeof(t_mini *), 1);
	*big_stack = NULL;
	while (lst)
	{
		small_stack = (t_list **)ft_malloc(sizeof(t_list *), 1);
		while (lst && lst->token != T_PIPE)
		{
			lst = add_big_stack1(small_stack, lst)->next;
		}
		lst_add_big_stack(big_stack, small_stack);
		if (lst)
			lst = lst->next;
	}
	return (big_stack);
}

void	delete_sq_dq(t_list **stack)
{
	t_list	*lst;
	char	*str;

	lst = *stack;
	while (lst)
	{
		if (!lst->content)
			;
		else if (lst->content[0] == D_QT || lst->content[0] == S_QT)
		{
			str = lst->content;
			lst->content = ft_substr(lst->content, 1, ft_strlen(str) - 2);
			free(str);
		}
		lst = lst->next;
	}
}

t_mini	**parsing(char *line1)
{
	char	*line;
	t_list	**stack;
	t_list	**new_stack;
	t_mini	**big_stack;

	line = ft_strtrim(line1, " ");
	if (!*line)
		return (NULL);
	if (!check_quote(line))
		return (free_and_print(line1, line), NULL);
	stack = (t_list **)ft_malloc(sizeof(t_list *), 1);
	*stack = NULL;
	line_handling(line, stack);
	tokenization(stack);
	if (syntax_error(stack))
		return (free_and_print(line, line1), free_stack(stack, 0), NULL);
	new_stack = (t_list **)ft_malloc(sizeof(t_list *), 1);
	*new_stack = NULL;
	expend(stack, new_stack);
	delete_sq_dq(new_stack);
	big_stack = add_big_stack(new_stack);
	free_stack(stack, 0);
	free_stack(new_stack, 1);
	return (free(line1), free(line), big_stack);
}
