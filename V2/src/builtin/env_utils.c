/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:15:22 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 01:16:42 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env_alphabetically(char **array)
{
	int	i;
	int	j;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				swap_strings(&array[i], &array[j]);
			j++;
		}
		i++;
	}
}

char	**copy_environ(t_env **env)
{
	char	**array;
	char	*temp;
	t_env	*ptr;
	int		i;

	array = (char **)malloc(sizeof(*array) * (ft_list_size(*env) + 1));
	if (array == NULL)
		return (NULL);
	ptr = *env;
	i = 0;
	while (ptr)
	{
		temp = ft_strjoin(ptr->value, "=");
		if (ft_strlen(ptr->result))
			array[i] = ft_strjoin(temp, ptr->result);
		else
			array[i] = ft_strjoin(temp, "''");
		free(temp);
		if (!array[i])
			free_array(array, i);
		ptr = ptr->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	index_existing_var(char *arg, t_env **env)
{
	int		len;
	int		i;
	t_env	*ptr;

	if (ft_strchr(arg, '='))
	{
		len = 0;
		while (arg[len] && (arg[len] != '='))
			len++;
	}
	else
		len = ft_strlen(arg);
	i = 0;
	ptr = *env;
	while (ptr)
	{
		if (ft_strncmp(ptr->value, arg, len) == 0)
			return (i);
		i++;
		ptr = ptr->next;
	}
	return (-1);
}

int	equal_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}
