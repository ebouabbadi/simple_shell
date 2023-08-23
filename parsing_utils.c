/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:45:46 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	pipe_handling(int i, t_list **stack)
{
	ft_lstadd_back(stack, ft_lstnew("|"));
	i++;
	return (i);
}

int	dq_handling(int i, t_list **stack, int start, char *line)
{
	int		len;
	char	*str;

	str = SNL;
	len = 0;
	while (line[i] && line[i + 1] != D_QT)
	{
		len++;
		i++;
	}
	str = ft_substr(line, start, len + 2);
	ft_lstadd_back(stack, ft_lstnew(str));
	i += 2;
	return (i);
}

int	sq_handling(int i, t_list **stack, int start, char *line)
{
	int		len;
	char	*str;

	str = SNL;
	len = 0;
	while (line[i] && line[i + 1] != S_QT)
	{
		len++;
		i++;
	}
	str = ft_substr(line, start, len + 2);
	ft_lstadd_back(stack, ft_lstnew(str));
	i += 2;
	return (i);
}

int	redc_handling(int i, t_list **stack, char *line)
{
	if (line[i] == INR && line[i + 1] == INR)
	{
		ft_lstadd_back(stack, ft_lstnew(HRDC));
		i += 2;
	}
	else if (line[i] == OUTR && line[i + 1] == OUTR)
	{
		ft_lstadd_back(stack, ft_lstnew(APND));
		i += 2;
	}
	else if (line[i] == INR && line[i + 1] != INR)
	{
		ft_lstadd_back(stack, ft_lstnew("<"));
		i++;
	}
	else if (line[i] == OUTR && line[i + 1] != OUTR)
	{
		ft_lstadd_back(stack, ft_lstnew(">"));
		i++;
	}
	return (i);
}

int	space_handlinge(int i, t_list **stack, int start, char *line)
{
	int		len;
	char	*str;

	str = SNL;
	len = 0;
	while (line[i] && line[i] == ' ')
	{
		len++;
		i++;
	}
	str = ft_substr(line, start, len);
	ft_lstadd_back(stack, ft_lstnew(str));
	return (i);
}
