/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 07:01:20 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*redirect_output(t_mini *lst, t_list *node)
{
	lst->f_write = open(node->next->content, O_CREAT
			| O_WRONLY | O_TRUNC, 0777);
	if (-1 == lst->f_write)
	{
		if (!node->next->content)
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		else
			msg_perror(node->next->content, 2);
		g_global.exit_status = 1;
		lst->if_exit = 1;
	}
	node = node->next;
	return (node);
}

t_list	*redirect_input(t_mini *lst, t_list *node)
{
	lst->f_read = open(node->next->content, O_RDONLY, 0777);
	if (-1 == lst->f_read)
	{
		g_global.exit_status = 1;
		if (!node->next->content)
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		else
		{
			msg_perror(node->next->content, 2);
			return (NULL);
		}
		lst->if_exit = 1;
	}
	node = node->next;
	return (node);
}

t_list	*redirect_output_in_append_mode(t_mini *lst, t_list *node)
{
	DIR	*dir;

	dir = opendir(node->next->content);
	if (dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->next->content, 2);
		ft_putstr_fd(": Is a directory", 2);
		g_global.exit_status = 1;
		lst->if_exit = 1;
		free(dir);
	}
	else
	{
		lst->f_write = open(node->next->content, O_CREAT
				| O_WRONLY | O_APPEND, 0777);
		if (-1 == lst->f_write)
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
	}
	node = node->next;
	return (node);
}

t_list	*redirections_handling(t_mini *lst, t_list *node, int *len)
{
	if (node->token == T_REDOUT)
		node = redirect_output(lst, node);
	else if (node->token == T_REDINP)
	{
		node = redirect_input(lst, node);
		if (!node)
			return (NULL);
	}
	else if (node->token == T_REDAPND)
		node = redirect_output_in_append_mode(lst, node);
	else if (node->token == T_HEREDOC)
	{
		node = heredoc(lst, node);
		if (!node)
			return (NULL);
	}
	else
	{
		(*len)++;
		node->if_add = 1;
	}
	return (node);
}

int	redirections(t_mini *lst)
{
	t_list	*node;
	int		len;

	len = 0;
	node = *(lst->stack);
	while (node)
	{
		if (!node->content)
		{
			node = node->next;
			continue ;
		}
		node = redirections_handling(lst, node, &len);
		if (!node)
			return (-1);
		node = node->next;
	}
	command_make(lst, len);
	g_global.last_cmd = lst->cmd[0];
	return (1);
}
