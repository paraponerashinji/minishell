/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:50:05 by aharder           #+#    #+#             */
/*   Updated: 2025/02/26 19:04:24 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_commands	*init_command_node(char **command)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	node->pipe_type = 2;
	node->command = command;
	node->next = NULL;
	return (node);
}

t_commands	*get_last_command(t_commands *a)
{
	while (a->next != NULL)
		a = a->next;
	return (a);
}

char	**merge_command(char **old, char **to_add)
{
	int		i;
	int		j;
	int		old_size;
	char	**output;

	old_size = array_size(old);
	output = malloc((old_size + array_size(to_add) + 1) * sizeof(char *));
	i = 0;
	while (old[i] != NULL)
	{
		output[i] = ft_strdup(old[i]);
		i++;
	}
	j = 0;
	while (to_add[j] != NULL)
		output[i++] = ft_strdup(to_add[j++]);
	output[i] = NULL;
	return (output);
}
