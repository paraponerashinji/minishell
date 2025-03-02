/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:02 by aharder           #+#    #+#             */
/*   Updated: 2025/03/02 02:52:55 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub) + 1) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(ft_getenv("PATH", env), ':');
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

int	executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp)
{
	int	exit_status;
	pid_t	p;
	char	*full_cmd;

	p = fork();
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		full_cmd = get_path(cmd, envp);
		execve(full_cmd, args, envp);
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

int	executefile(char *cmd, char **args, int i_fd, int o_fd, char **envp)
{
	int	exit_status;
	pid_t	p;
	char	*full_cmd;
	char	current_path[1024];

	p = fork();
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		getcwd(current_path, sizeof(current_path));
		full_cmd = ft_strjoin(current_path, cmd);
		execve(full_cmd, args, envp);
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

int	is_command(char	*str)
{
	char    *commands[] = {"cd", "echo", "exit", "pwd", "wc", "unset", "env"};
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(str, commands[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strchrpos(char *str, int searchedChar)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == (char)searchedChar)
			return (i);
		str++;
		i++;
	}
	if (searchedChar == '\0')
		return (0);
	return (0);
}
void	check_env(t_commands *temp)
{
	int	i[5];
	char	*str;
	char	*buffer;
	char	*buff2;

	i[0] = 0;
	while (temp->command[i[0]] != NULL)
	{
		i[1] = ft_strlen(temp->command[i[0]]);
		i[2] = ft_strchrpos(temp->command[i[0]], '$');
		if (temp->command[i[0]][0] == '"' && temp->command[i[0]][i[1] - 1] == '"' && i[2])
		{
			i[3] = i[2];
			while (temp->command[i[0]][i[3]] != ' ' && temp->command[i[0]][i[3]] != '"')
				i[3]++;
			i[3] = i[3] - i[2];
			buffer = ft_substr(temp->command[i[0]], i[2], i[3]);
			str = getenv(&buffer[1]);
			buff2 = temp->command[i[0]];
			temp->command[i[0]] = ft_replacesubstr(buff2, buffer, str);
			free(buff2);
			free(buffer);
		}
		else if (temp->command[i[0]][0] == '$')
		{
			i[3] = i[2];
			while (temp->command[i[0]][i[3]] != ' ' && temp->command[i[0]][i[3]] != '\0')
				i[3]++;
			i[3] = i[3] - i[2];
			buffer = ft_substr(temp->command[i[0]], i[2], i[3]);
			str = getenv(&buffer[1]);
			buff2 = temp->command[i[0]];
			temp->command[i[0]] = ft_replacesubstr(buff2, buffer, str);
			free(buff2);
			free(buffer);
		}
		i[0]++;
	}
}

int	find_i_red(t_io_red *redirection)
{
	t_io_red	*temp;
	int	input_fd;

	temp = redirection;
	input_fd = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		if (temp->in_or_out == INPUT)
		{
			if (input_fd)
				close(input_fd);
			input_fd = open(temp->file, O_RDONLY);
		}
		temp = temp->next;
	}
	return (input_fd);
}

void	copy(int buff_fd, int *o_fd, int size)
{
	char	*line;
	int	i;

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

void	free_and_close(int *fd, int size)
{
	int	i;
	
	i = 0;
	while (size > i)
		close(fd[i++]);
	free(fd);
}
void	write_output(int buff_fd, t_io_red *redirection)
{
	t_io_red	*temp;
	int	*output_fd;
	int	i;

	i = 0;
	temp = redirection;
	while (temp != NULL)
	{
		if (temp->in_or_out == 7)
		{
			i++;
		}
		temp = temp->next;
	}
	temp = redirection;
	if (i == 0)
	{
		copy_single(buff_fd, 1);
		return;
	}
	output_fd = malloc((i + 1) * sizeof(int));
	i = 0;
	while (temp != NULL)
	{
		if (temp->in_or_out == OUTPUT)
		{
			output_fd[i] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		temp = temp->next;
	}
	copy(buff_fd, output_fd, i);
	free_and_close(output_fd, i);
	close(buff_fd);
}
/*
void	manage_pipe(t_commands *commands, t_io_red *redirection, char **envp)
{
	int	status;
	int	p_fd[2];
	int	buffer;
	t_commands	*temp;

	temp = commands;
	status = 0;
	while (temp != NULL)
	{
		pipe(p_fd);
		if (temp->pipe_type == 1 && status != 0)
			status = createpipes(temp, redirection, p_fd, envp);
		else if (temp->pipe_type == 2)
			status = createpipes(temp, redirection, p_fd, envp);
		else if (temp->pipe_type == 3 && status == 0)
			status = createpipes(temp, redirection, p_fd, envp);
		if ((temp->pipe_type == 3 && status == 0) || (temp->pipe_type == 2) || (temp->pipe_type == 1 && status != 0))
		{
			close(buffer);
			buffer = p_fd[0];
		}
		temp = temp->next;
	}
	write_output(buffer, redirection);
}
*/
int	createpipes(t_commands *commands, t_io_red *redirection, char **envp)
{
	int	status;
	int	p_fd[2];
	int	b_fd[2];
	int	buffer;
	t_commands	*temp;

	buffer = find_i_red(redirection);
	if (buffer == -1) return (-1);
	temp = commands;
	if (pipe(b_fd) == -1) {
		perror("pipe error");
		return (-1);
	}
	while (temp != NULL)
	{
		check_env(temp);
		if (pipe(p_fd) == -1) {
			perror("pipe error");
			return (-1);
		}
		if (temp->pipe_type == 3 || temp->pipe_type == 2 || temp->pipe_type == 1)
		{
			if (ft_strncmp(temp->command[0], "./", 2) == 0)
				status = executefile(&temp->command[0][1], temp->command, buffer, p_fd[1], envp);
			else if (is_command(temp->command[0]) != -1)
				status = executecommand(temp->command[0], temp->command, buffer, p_fd[1], envp);
			else
			{
				printf("%s: command not found\n", temp->command[0]);
				status = 127;
			}
			close(p_fd[1]);
			if (temp->next != NULL)
			{
				if ((temp->next->pipe_type == 3 && status != 0) || (temp->next->pipe_type == 1 && status == 0))
				{
					break;
				}
			}
			buffer = p_fd[0];
		}
		temp = temp->next;
	}
	dup2(p_fd[0], b_fd[0]);
	close(p_fd[0]);
	close(p_fd[1]);
	close(b_fd[1]);
	write_output(b_fd[0], redirection);
	return (1);
}
