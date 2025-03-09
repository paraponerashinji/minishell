/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:09:57 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 21:38:00 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_commands(t_commands *commands, t_env *env, int b_fd[2], int b)
{
	t_commands	*t;
	int			s;
	int			p_fd[2];

	t = commands;
	init_pipes(p_fd, b_fd);
	while (t != NULL)
	{
		check_env(t, env);
		pipe(p_fd);
		s = execute(t, b, p_fd, env);
		if (t->next != NULL)
		{
			if (t->next->pipe_type == 3 && s != 0)
				break ;
			if (t->next->pipe_type == 1 && s == 0)
				break ;
			close(p_fd[1]);
		}
		b = p_fd[0];
		t = t->next;
	}
	dup2(p_fd[0], b_fd[0]);
	close_pipes(p_fd);
	close(b_fd[1]);
}

int	createpipes(t_commands *commands, t_io_red *redirection, t_env *env)
{
	int	b_fd[2];
	int	buffer;

	buffer = find_i_red(redirection);
	process_commands(commands, env, b_fd, buffer);
	close(b_fd[1]);
	write_output(b_fd[0], redirection);
	return (1);
}

int	is_exec_command(char *str)
{
	char	*commands[] = {"echo", "env", "pwd"};
	int		i;

	i = 0;
	while (i < 3)
	{
		if (ft_strcmp(str, commands[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_other_command(char *str)
{
	char	*commands[] = {"export", "unset", "cd"};
	int		i;

	i = 0;
	while (i < 3)
	{
		if (ft_strcmp(str, commands[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	init_pipes(int p_fd[2], int b_fd[2])
{
	pipe(b_fd);
	if (p_fd != NULL)
		pipe(p_fd);
}
