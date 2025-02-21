/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:02 by aharder           #+#    #+#             */
/*   Updated: 2025/02/21 15:37:44 by aharder          ###   ########.fr       */
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

void	executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp)
{
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
		waitpid(p, NULL, 0);
}

void	executefile(char *cmd, char **args, int i_fd, int o_fd, char **envp)
{
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
		waitpid(p, NULL, 0);
}

int	is_command(char	*str)
{
	char    *commands[] = {"cd", "echo", "exit", "pwd", "export", "unset", "env"};
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
int	createpipes(t_commands *commands, t_io_red *redirection, char **envp)
{
	int	p_fd[2];
	int	buffer;
	t_commands	*temp;

	(void)redirection;
	buffer = STDIN_FILENO;
	temp = commands;
	while (temp != NULL)
	{
		if (temp->next != NULL)
			pipe(p_fd);
		else
			p_fd[1] = STDOUT_FILENO;
		if (ft_strncmp(temp->command[0], "./", 2) == 0)
			executefile(&temp->command[0][1], temp->command, buffer, p_fd[1], envp);
		else if (is_command(temp->command[0]) != -1)
			executecommand(temp->command[0], temp->command, buffer, p_fd[1], envp);
		else
			printf("%s: command not found\n", temp->command[0]);
		if (temp->next != NULL)
			close(p_fd[1]);
		if (buffer != 0)
			close(buffer);
		buffer = p_fd[0];
		temp = temp->next;
	}
	return (1);
}
