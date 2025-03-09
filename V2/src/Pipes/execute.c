/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:55:16 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 21:39:06 by aharder          ###   ########.fr       */
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
	else if (is_exec_command(t->command[0]) != -1)
		status = executebuiltin(t->command, b, p_fd[1], env);
	else if (is_other_command(t->command[0]) != -1)
		status = commandbuiltin(t->command, env);
	else
		status = executecommand(t->command[0], t->command, b, p_fd[1]);
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
		free(full_cmd);
		exit(1);
	}
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
		exit(1);
	}
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
		free(full_cmd);
		exit(1);
	}
	else
		waitpid(p, &exit_status, 0);
	return (exit_status);
}

int	executebuiltin(char **cmd, int i_fd, int o_fd, t_env *envi)
{
	int	exit_status;
	pid_t		p;

	p = fork();
	if (p == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		dup2(o_fd, STDOUT_FILENO);
		if (strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
			echo(cmd);
		else if (strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
			env(&envi);
		else if (strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
			pwd();
		exit(1);
	}
	else
		waitpid(p, &exit_status, 0);
	return (exit_status);	
}
