/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:32:39 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:56:45 by aharder          ###   ########.fr       */
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

int	unset_green_light(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (0);
	return (1);
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
			if (arg_var_has_valid_chars(args[i]) && unset_green_light(args[i]))
				ft_list_remove_if(env, args[i], ft_strcmp);
			else
			{
				ft_putstr_fd("unset: \'", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("\' is not a valid identifier\n", 2);
			}
			i++;
		}
	}
	return (0);
}