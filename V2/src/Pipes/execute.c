/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:55:16 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 02:09:20 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_commands *t, int b, int p_fd[2], t_env *env)
{
	int	status;

	if (t->command[0][0] == '/' && access(t->command[0], F_OK | X_OK) == 0)
		status = executefullfile(t->command[0], t->command, b, p_fd[1]);
	else if (ft_strncmp(t->command[0], "./", 2) == 0)
	{
		if (!access(&t->command[0][2], F_OK | X_OK))
			status = executefile(t->command, b, p_fd[1], env);
		else
		{
			printf("%s: file not found\n", t->command[0]);
			status = 127;
		}
	}
	else if (is_command(t->command[0]) != -1)
		status = executecommand(t->command[0], t->command, b, p_fd[1]);
	else
	{
		printf("%s: command not found\n", t->command[0]); // TODO replace this part with normal execution
		status = 127;
	}
	return (status);
}

int	executefile(char **args, int i_fd, int o_fd, t_env *env)
{
	int			exit_status;
	pid_t		p;
	extern char	**environ;
	char		*full_cmd;
	char		current_path[1024];

	(void)env;
	p = fork();
	exit_status = 1;
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		getcwd(current_path, sizeof(current_path));
		full_cmd = ft_strjoin(current_path, &args[0][1]);
		execve(&args[0][1], args, environ);
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

int	executefullfile(char *cmd, char **args, int i_fd, int o_fd)
{
	int			exit_status;
	pid_t		p;
	extern char	**environ;

	p = fork();
	exit_status = 1;
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		execve(cmd, args, environ);
		perror("fail file");
		exit(1);
	}
	else if (p == -1)
		ft_printf("fork error");
	else
		waitpid(p, &exit_status, 0);
	return (exit_status);
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
