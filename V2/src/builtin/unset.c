/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:32:39 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 01:08:43 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_list_remove_if(t_env **begin_list, char *arg, int (*ft_strcmp)())
{
	t_env	*current;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	current = *begin_list;
	if (ft_strcmp(current->value, arg) == 0)
	{
		*begin_list = current->next;
		free(current->value);
		free(current->result);
		free(current);
		ft_list_remove_if(begin_list, arg, ft_strcmp);
	}
	else
	{
		current = *begin_list;
		ft_list_remove_if(&current->next, arg, ft_strcmp);
	}
}

int	unset(char **args, t_env **env)
{
	int	i;

	if (!args[1])
		return (1);
	else
	{
		i = 1;
		while (args[i])
		{
			ft_list_remove_if(env, args[i], ft_strcmp);
			i++;
		}
	}
	return (0);
}
