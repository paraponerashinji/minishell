/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:11:46 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:55:58 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **array, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	swap_strings(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

int	ft_list_size(t_env *begin_list)
{
	int		size;
	t_env	*current;

	size = 0;
	current = begin_list;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	print_export(t_env **env)
{
	char	**temp;
	int		j;

	temp = copy_environ(env);
	sort_env_alphabetically(temp);
	j = 0;
	while (temp[j])
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s\n", temp[j]);
		j++;
	}
	free_split(temp);
	return (0);
}

void	ft_env_push_back(t_env **begin_list, char *data)
{
	t_env	*new_elem;
	t_env	*current;

	new_elem = ft_create_var(data);
	if (*begin_list == NULL)
	{
		*begin_list = new_elem;
	}
	else
	{
		current = *begin_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_elem;
	}
}