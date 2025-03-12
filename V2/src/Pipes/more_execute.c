/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:20:52 by aharder           #+#    #+#             */
/*   Updated: 2025/03/12 00:35:50 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commandbuiltin(char **arg, t_env *env)
{
	int	exit_status;

	(void)env;
	exit_status = 0;
	if (strcmp(arg[0], "cd") == 0)
	{
		exit_status = cd(arg);
	}
	else if (strcmp(arg[0], "export") == 0)
		exit_status = export(arg, &env);
	else if (strcmp(arg[0], "unset") == 0)
		exit_status = unset(arg, &env);
	else if (strcmp(arg[0], "exit") == 0)
		ft_exit(env);
	return (exit_status);
}

char	*get_path(char *cmd, t_env *env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(ft_getenv(env, "PATH"), ':');
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
