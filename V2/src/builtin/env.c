/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:25:45 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:54:24 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env(t_env **env, char **cmd)
{
	t_env	*ptr;
	int	i;

	ptr = *env;
	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "env") != 0)
		{
			ft_putstr_fd("env: \'", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("\': No such file or directory", 2);
			exit(1);
		}
		i++;
	}
	while (ptr)
	{
		if (ptr->result)
		{
			if ((strcmp(ptr->value, "?") != 0) && (strcmp(ptr->value, "&") != 0)
			&& (strcmp(ptr->value, "+") != 0) && (strcmp(ptr->result, "''") != 0))
				printf("%s=%s\n", ptr->value, ptr->result);
		}
		ptr = ptr->next;
	}
	return (0);
}