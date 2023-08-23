/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:48:42 by ebouabba          #+#    #+#             */
/*   Updated: 2023/08/23 23:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	verification1(char c)
{
	if (c == SPC || c == D_QT || c == S_QT
		|| c == '|' || c == INR || c == OUTR)
		return (1);
	return (0);
}

int	mot_handling(int i, t_list **stack, int start, char *line)
{
	int		len;
	char	*str;

	str = SNL;
	len = 0;
	while (line[i] && !verification1(line[i]))
	{
		len++;
		i++;
	}
	str = ft_substr(line, start, len);
	ft_lstadd_back(stack, ft_lstnew(str));
	return (i);
}

static	void	check(char *line, int *dq, int *sq)
{
	if (*line == D_QT)
	{
		if (*dq == 0 && *sq == 0)
			*dq = 1;
		else
			*dq = 0;
	}
	else if (*line == S_QT)
	{
		if (*sq == 0 && *dq == 0)
			*sq = 1;
		else
			*sq = 0;
	}
}

int	check_quote(char *line)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (*line)
	{
		check(line, &dq, &sq);
		line++;
	}
	if (sq == 1 || dq == 1)
		return (0);
	return (1);
}

void	line_handling(char *line, t_list **stack)
{
	int	i;
	int	start;

	i = 0;
	while (line[i])
	{
		start = i;
		if (line[i] == D_QT)
			i = dq_handling(i, stack, start, line);
		else if (line[i] == S_QT)
			i = sq_handling(i, stack, start, line);
		else if ((line[i] == INR && line[i + 1] == INR)
			|| (line[i] == OUTR && line[i + 1] == OUTR)
			|| (line[i] == INR && line[i + 1] != INR)
			|| (line[i] == OUTR && line[i + 1] != OUTR))
			i = redc_handling(i, stack, line);
		else if (line[i] == '|')
			i = pipe_handling(i, stack);
		else if (line[i] == SPC)
			i = space_handlinge(i, stack, start, line);
		else
			i = mot_handling(i, stack, start, line);
	}
}
