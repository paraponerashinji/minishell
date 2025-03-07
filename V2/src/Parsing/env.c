/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:22:07 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 15:59:02 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_first_command(t_commands **a, char *s, char **envp)
{
	t_commands	*buffer;
	t_commands	*last;

	buffer = malloc(sizeof(t_commands));
	buffer->pipe_type = 2;
	buffer->command = second_split(s, ' ');
	buffer->env = init_env(envp);
	buffer->next = NULL;
	if (!*a)
		*a = buffer;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = buffer;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int	i;
	int	j;
	char	*value;
	char	*result;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '\0' && envp[i][j] != '=')
			j++;
		value = ft_substr(envp[i], 0, j);
		result = ft_substr(envp[i], j, ft_strlen(envp[i]));
		add_env(&env, value, result);
		i++;
	}
	return (env);	
}

void	add_env(t_env	**a, char *value, char *result)
{
	t_env	*temp;
	t_env	*last;

	temp = malloc(sizeof(t_env));
	temp->value = value;
	temp->result = result;
	temp->next = NULL;
	if (!*a)
		*a = temp;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = temp;
	}
}
