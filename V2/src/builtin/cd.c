/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:29:13 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 21:48:50 by aharder          ###   ########.fr       */
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

int	cd(char **args)
{
	char	*root;

	if (!args[1] && args[1] == NULL)
	{
		root = get_root_directory();
		if (chdir(root) != 0)
			printf("cd: root error\n");
		else
		{
			free(root);
			return (0);
		}
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
	return (0);
}