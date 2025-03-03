/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:02 by aharder           #+#    #+#             */
/*   Updated: 2025/03/03 02:32:32 by aharder          ###   ########.fr       */
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
	exit_status = 1;
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
	exit_status = 1;
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

char	**get_filenames(void)
{
	struct dirent	*entry;
	DIR	*dp;
	char	**filenames;
	int count;
	int	i;
	
	i = 0;
	count = 0;
	dp = opendir(".");
	if (dp == NULL)
	{
		perror("opendir");
		return NULL;
	}

	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			count++;
		entry = readdir(dp);
        }
        closedir(dp);
        filenames = malloc((count + 1) * sizeof(char *));
        dp = opendir(".");
       	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			filenames[i++] = ft_strdup(entry->d_name);
		entry = readdir(dp);
        }
        filenames[i] = NULL;
        closedir(dp);
        return (filenames);
}

char	**insert_files(char **command, int index)
{
	char	**filenames;
	char	**output;
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	filenames = get_filenames();
	output = malloc((array_size(filenames) + array_size(command) + 1) * sizeof(char *));
	while (i < index)
	{
		output[i] = ft_strdup(command[i]);
		i++;
	}
	while (filenames[j] != NULL)
	{
		output[index + j] = ft_strdup(filenames[j]);
		j++;
	}
	k = index + 1;
	while (command[k] != NULL)
		output[index + j++] = ft_strdup(command[k++]);
	output[index + j] = NULL;
	free_split(filenames);
	free_split(command);
	return (output);
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
		else if (temp->command[i[0]][0] == '*' && temp->command[i[0]][1] == '\0')
		{
			temp->command = insert_files(temp->command, i[0]);
		}
		i[0]++;
	}
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
			break;
		}
		write(p_fd[1], heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
}

int	find_i_red(t_io_red *redirection)
{
	t_io_red	*temp;
	int	input_fd[2];

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
		if (temp->in_or_out == 7 || temp->in_or_out == 6)
			i++;
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
