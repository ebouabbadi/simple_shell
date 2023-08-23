/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouabba <ebouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 07:51:18 by hbadr             #+#    #+#             */
/*   Updated: 2022/10/26 17:59:12 by ebouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct env
{
	char			*vallue;
	char			*name;
	struct env		*next;
}	t_env;

typedef struct s_list
{
	int				if_add;
	int				token;
	int				expend;
	int				if_expend;
	int				sq;
	int				dq;
	int				if_expend_echo;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_mini
{
	int				if_exit;
	int				size;
	int				std_in;
	int				std_out;
	int				f_read;
	int				f_write;
	char			**cmd;
	char			*path;
	char			*mot;
	char			**envp;
	char			*pwd;
	t_env			**envs;
	char			*file_heredoc;
	t_list			**stack;
	struct s_mini	*next;
}	t_mini;

typedef struct trash
{
	void			*p;
	struct trash	*next;
}	t_trash;

typedef struct s_global
{
	t_env	**envs;
	char	*msg_old_pwd;
	int		prinf_old_pwd;
	char	*old_pwd;
	int		exit_status;
	int		skip;
	int		if_fork;
	char	*last_cmd;
	t_trash	**trash;
	char	*pwd;
	pid_t	pid;
}	t_global;

#endif