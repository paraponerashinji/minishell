/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:09:57 by aharder           #+#    #+#             */
/*   Updated: 2025/02/27 01:26:06 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	process_commands(t_commands *commands, int p_fd[2], int b_fd[2], int buffer)
{
	t_commands	*temp;

	temp = commands;
	init_pipes(p_fd, b_fd);
	while (temp != NULL)
	{
		check_env(temp);
		if (temp->next != NULL)
			pipe(p_fd);
		else
			p_fd[1] = b_fd[1];
		execute_command(temp, buffer, p_fd)
		if (temp->next != NULL)
			close(p_fd[1]);
		close_pipes(buffer);
		buffer = p_fd[0];
		temp = temp->next;
	}
}

void	execute_command(t_commands *temp, int buffer, int p_fd[2])
{
	if (ft_strncmp(temp->command[0], "./", 2) == 0)
		executefile(&temp->command[0][1], temp->command, buffer, p_fd[1], envp);
	else if (is_command(temp->command[0]) != -1)
		executecommand(temp->command[0], temp->command, buffer, p_fd[1], envp);
	else
		printf("%s: command not found\n", temp->command[0]);
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
