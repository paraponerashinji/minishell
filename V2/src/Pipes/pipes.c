/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:09:57 by aharder           #+#    #+#             */
/*   Updated: 2025/03/06 17:48:40 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_commands(t_commands *commands, int p_fd[2], int b_fd[2], int buffer)
{
	t_commands	*temp;
	int			status;

	temp = commands;
	init_pipes(p_fd, b_fd);
	while (temp != NULL)
	{
		check_env(temp);
		pipe(p_fd);
		status = execute(temp, buffer, p_fd);
		if (temp->next != NULL)
		{
			if ((temp->next->pipe_type == 3 && status != 0) || (temp->next->pipe_type == 1 && status == 0))
				break ;
			close(p_fd[1]);
		}
		buffer = p_fd[0];
		temp = temp->next;
	}
	dup2(p_fd[0], b_fd[0]);
	close(p_fd[0]);
	close(p_fd[1]);
	close(b_fd[1]);
}

int	createpipes(t_commands *commands, t_io_red *redirection)
{
	int	p_fd[2];
	int	b_fd[2];
	int	buffer;

	buffer = find_i_red(redirection);
	process_commands(commands, p_fd, b_fd, buffer);
	close(b_fd[1]);
	write_output(b_fd[0], redirection);
	return (1);
}

int	is_command(char	*str)
{
	char	*commands[] = {"cd", "echo", "exit", "export", "wc", "unset", "env"};
	int		i;

	i = 0;
	while (i < 7)
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

void	close_pipes(int fd)
{
	if (fd != 0)
		close(fd);
}
