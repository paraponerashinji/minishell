/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:22:07 by aharder           #+#    #+#             */
/*   Updated: 2025/04/13 22:13:11 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		j;
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
		result = ft_substr(envp[i], j + 1, ft_strlen(envp[i]));
		add_env(&env, value, result);
		i++;
	}
	add_exit_status(0, &env);
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

void	rm_env(t_env **a, char *value)
{
	t_env	*temp;
	t_env	*last;

	temp = *a;
	if (strcmp(temp->value, value) == 0)
	{
		*a = temp->next;
		free(temp->value);
		free(temp->result);
		free(temp);
		return ;
	}
	while (temp->next != NULL)
	{
		if (strcmp(temp->next->value, value) == 0)
		{
			last = temp->next;
			temp->next = temp->next->next;
			free(last->value);
			free(last->result);
			free(last);
			return ;
		}
		temp = temp->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->value);
		free(temp->result);
		free(temp);
	}
}
