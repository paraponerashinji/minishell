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

#include "../include/minishell.h"

void	free_and_close(int *fd, int size)
{
	int	i;

	i = 0;
	while (size > i)
		close(fd[i++]);
	free(fd);
}

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

int	executecommand(char *cmd, char **args, int i_fd, int o_fd)
{
	int			exit_status;
	pid_t		p;
	extern char	**environ;
	char		*full_cmd;

	p = fork();
	exit_status = 1;
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		full_cmd = get_path(cmd);
		execve(full_cmd, args, environ);
		perror("fail command");
		free(full_cmd);
		exit(1);
	}
	else if (p == -1)
		ft_printf("fork error");
	else
		waitpid(p, &exit_status, 0);
	return (exit_status);
}

char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_split(s_cmd);
			return (exec);
		}
		free(exec);
	}
	free_split(allpath);
	free_split(s_cmd);
	return (cmd);
}

int	executefile(char *cmd, char **args, int i_fd, int o_fd)
{
	int			exit_status;
	pid_t		p;
	extern char	**environ;
	char		*full_cmd;
	char		current_path[1024];

	p = fork();
	exit_status = 1;
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		getcwd(current_path, sizeof(current_path));
		full_cmd = ft_strjoin(current_path, cmd);
		execve(full_cmd, args, environ);
		perror("fail file");
		free(full_cmd);
		exit(1);
	}
	else if (p == -1)
		ft_printf("fork error");
	else
		waitpid(p, &exit_status, 0);
	return (exit_status);
}

void	copy(int buff_fd, int *o_fd, int size)
{
	char	*line;
	int		i;

	line = get_next_line(buff_fd);
	if (line == NULL)
		printf("erreur gnl");
	while (line != NULL)
	{
		i = 0;
		while (size > i)
		{
			write(o_fd[i++], line, ft_strlen(line));
		}
		free(line);
		line = get_next_line(buff_fd);
	}
}

void	copy_single(int buff_fd, int o_fd)
{
	char	*line;

	line = get_next_line(buff_fd);
	while (line != NULL)
	{
		write(o_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(buff_fd);
	}
}

void	write_output(int buff_fd, t_io_red *redirection)
{
	t_io_red	*temp;
	int			*output_fd;
	int			i;

	i = 0;
	temp = redirection;
	while (temp != NULL)
	{
		if (temp->in_or_out == 7 || temp->in_or_out == 6)
			i++;
		temp = temp->next;
	}
	temp = redirection;
	if (i == 0)
	{
		copy_single(buff_fd, 1);
		return ;
	}
	output_fd = malloc((i + 1) * sizeof(int));
	i = 0;
	while (temp != NULL)
	{
		if (temp->in_or_out == 7)
			output_fd[i++] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->in_or_out == 6)
			output_fd[i++] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		temp = temp->next;
	}
	copy(buff_fd, output_fd, i);
	free_and_close(output_fd, i);
	close(buff_fd);
}

void	get_heredoc(int *p_fd, char *end)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (ft_strcmp(heredoc, end) == 0)
		{
			free(heredoc);
			break ;
		}
		write(p_fd[1], heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
}

void	free_cmd(t_commands **a)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		while (tmp->command[i] != NULL)
			free(tmp->command[i++]);
		free(tmp->command);
		free(tmp);
	}
}

void	free_red(t_io_red **a)
{
	t_io_red	*tmp;

	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		free(tmp->file);
		free(tmp);
	}
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

int	find_i_red(t_io_red *redirection)
{
	t_io_red	*temp;
	int			input_fd[2];

	temp = redirection;
	input_fd[0] = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		if (temp->in_or_out == 5)
		{
			if (input_fd[0])
				close(input_fd[0]);
			input_fd[0] = open(temp->file, O_RDONLY);
		}
		if (temp->in_or_out == 4)
		{
			if (input_fd[0])
				close(input_fd[0]);
			pipe(input_fd);
			get_heredoc(input_fd, temp->file);
			close(input_fd[1]);
		}
		temp = temp->next;
	}
	return (input_fd[0]);
}

int	execute(t_commands *temp, int buffer, int p_fd[2])
{
	int	status;

	if (access(temp->command[0], F_OK | X_OK) == 0)
		status = executecommand(temp->command[0], temp->command, buffer, p_fd[1]);
	if (ft_strncmp(temp->command[0], "./", 2) == 0)
		status = executefile(&temp->command[0][1], temp->command, buffer, p_fd[1]);
	else if (is_command(temp->command[0]) != -1)
		status = executecommand(temp->command[0], temp->command, buffer, p_fd[1]);
	else
	{
		printf("%s: command not found\n", temp->command[0]);
		status = 127;
	}
	return (status);
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
