/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:56:38 by hbadr             #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	heredoc_handling_2(t_list *node, int fd, char *inpt)
{
	if (!*inpt)
	{
		ft_putchar_fd('\n', fd);
		free(inpt);
		return (0);
	}
	if (strcmp(inpt, node->next->content) == 0)
	{
		free(inpt);
		return (1);
	}
	if (node->next->if_expend)
		ft_putendl_fd(inpt, fd);
	else
		expend_inside_herdoc(fd, inpt);
	free(inpt);
	return (0);
}

t_list	*heredoc_handling(t_list *node, int fd)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("> ");
		if (!inpt && g_global.skip == 0)
		{
			free(inpt);
			break ;
		}
		if (!inpt || g_global.skip == 1)
		{
			free(inpt);
			return (NULL);
		}
		if (heredoc_handling_2(node, fd, inpt))
			break ;
		else
			continue ;
	}
	return (node);
}

t_list	*heredoc(t_mini *lst, t_list *node)
{
	int	fd;

	fd = open(lst->file_heredoc, O_CREAT | O_TRUNC, 0777);
	fd = open(lst->file_heredoc, O_WRONLY);
	signal(SIGINT, fanc_aplic);
	rl_event_hook = get_c;
	if (!(heredoc_handling(node, fd)))
		return (NULL);
	lst->f_read = open(lst->file_heredoc, O_RDONLY);
	node = node->next;
	return (node);
}
