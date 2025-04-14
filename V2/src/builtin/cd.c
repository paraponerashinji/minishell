/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:29:13 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:54:06 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_root_directory(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "HOME=", 5) == 0)
			return (ft_substr(environ[i], 5, ft_strlen(environ[i]) - 5));
		i++;
	}
	return (NULL);
}

void	update_pwd(t_env **env)
{
	char	**args;
	char	*pwd;
	char	*copy;
	char	buf[1096];

	pwd = getcwd(buf, 1096);
	args = malloc(3 * sizeof(char *));
	args[0] = ft_strdup("export");
	copy = ft_strdup(pwd);
	args[1] = ft_strjoin("PWD=", copy);
	args[2] = NULL;
	export(args, env);
	free(args[0]);
	free(copy);
	free(args[1]);
	free(args);
	//free(pwd);
}

void	update_old_pwd(t_env **env, char *oldwd)
{
	char	**args;
	char	*copy;

	if (oldwd == NULL || oldwd[0] == '\0')
		return ;
	args = malloc(3 * sizeof(char *));
	args[0] = ft_strdup("export");
	copy = ft_strdup(oldwd);
	args[1] = ft_strjoin("OLDPWD=", copy);
	args[2] = NULL;
	export(args, env);
	free(args[0]);
	free(copy);
	free(args[1]);
	free(args);
	//free(pwd);
}

int	cd(char **args, t_env **env)
{
	char	*root;
	char	*cwd;
	char	buf[1096];
	
	cwd = getcwd(buf, 1096);
	if ((!args[1] && args[1] == NULL) || (args[1] && ft_strcmp(args[1], "~") == 0))
	{
		root = get_root_directory();
		if (chdir(root) != 0)
			printf("cd: root error\n");
		else
		{
			update_old_pwd(env, cwd);
			update_pwd(env);
			free(root);
			return (0);
		}
		free(cwd);
		return (1);
	}
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (chdir(args[1]) != 0)
	{
		printf("cd : error\n");
		return (1);
	}
	update_old_pwd(env, cwd);
	update_pwd(env);
	return (0);
}