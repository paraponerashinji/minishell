/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:16:22 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:55:44 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ptr_result(char *arg)
{
	char	*result;
	int	len;

	len = equal_pos(arg) + 1;
	while (arg[len] && arg[len] != ';' && arg[len] != '|' && arg[len] != '$')
	{
		len++;
	}
	len = len - equal_pos(arg);
	result = ft_substr(arg, equal_pos(arg) + 1, len - 1);
	return (result);
}

int	update(char *arg, int index, t_env **env)
{
	int		i;
	t_env	*ptr;

	i = 0;
	ptr = *env;
	while (i < index)
	{
		ptr = ptr->next;
		i++;
	}
	if (ft_strchr(arg, '='))
	{
		free(ptr->value);
		free(ptr->result);
		ptr->value = ft_substr(arg, 0, equal_pos(arg));
		ptr->result = ptr_result(arg);
		//ptr->result = ft_substr(arg, equal_pos(arg) + 1, ft_strlen(arg) - 1);
	}
	return (0);
}

t_env	*ft_create_var(char *arg)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (new_elem == NULL)
		return (NULL);
	if (ft_strchr(arg, '='))
	{
		new_elem->value = ft_substr(arg, 0, equal_pos(arg));
		new_elem->result = ptr_result(arg);
		//new_elem->result = ft_substr(arg, equal_pos(arg) + 1, ft_strlen(arg) - 1);
		new_elem->next = NULL;
	}
	else
	{
		new_elem->value = ft_strdup(arg);
		new_elem->result = NULL;
		//new_elem->result = ft_strdup("''");
		new_elem->next = NULL;
	}
	return (new_elem);
}

int	export(char **args, t_env **env)
{
	int		i;
	int		index;

	index = -1;
	if (args == NULL || args[1] == NULL || args[1][0] == '\0')
	//if ((!args[1] || args[1] == NULL || args[1][0] == '\0') && !args[2])
		return (print_export(env));
	else
	{
		i = 1;
		while (args[i])
		{
			if (arg_var_has_valid_chars(args[i]) && arg_val_has_valid_chars(args[i]))
			{
				index = index_existing_var(args[i], env);
				if (index >= 0)
					update(args[i], index, env);
				else
					ft_env_push_back(env, args[i]);
			}
			else
				printf("export: invalid character\n");
			i++;
		}
	}
	return (0);
}