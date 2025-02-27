/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:21:14 by aharder           #+#    #+#             */
/*   Updated: 2025/02/19 15:23:06 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_command(t_commands **a, char *splitted, pipetype type)
{
	t_commands	*buffer;
	t_commands	*last;

	buffer = malloc(sizeof(t_commands));
	buffer->pipe_type = type;
	buffer->command = second_split(splitted, ' ');
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

t_commands	*init_command_node(char **command)
{
	t_commands	*node;

	node = malloc(sizeof(t_commands));
	node->pipe_type = PIPE;
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

void	add_buff_to_last(t_commands **a, char *str)
{
	t_commands	*last;
	int	i;
	char		**buffer_split;
	char		**new_command;

	i = 0;
	buffer_split = second_split(str, ' ');
	free(str);
	if (!*a)
		*a = init_command_node(buffer_split);
	else
	{
		last = get_last_command(*a);
		new_command = merge_command(last->command, buffer_split);
		while (last->command[i] != NULL)
			free(last->command[i++]);
		free(last->command);
		last->command = new_command;
	}
	free(buffer_split);
}

char	*add_io(t_io_red **a, char *splitted, iotype type)
{
	t_io_red	*buffer;
	t_io_red	*last;
	char		*output;
	buffer = malloc(sizeof(t_io_red));
	buffer->in_or_out = type;
	buffer->file = first_word(splitted);
	buffer->next = NULL;
	output = rm_first_word(splitted);
	if (!*a)
		*a = buffer;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = buffer;
	}
	return (output);
}

char	*first_word(char *str)
{
	int	i;
	int	k;
	
	char	*output;

	i = 0;
	k = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i] != '\0')
	{
		i++;
		k++;
	}
	output = malloc((k + 1) * sizeof(char));
	i -= k;
	k = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		output[k++] = str[i++];
	}
	output[k] = '\0';
	return (output);
}

char	*rm_first_word(char *str)
{
	int	i;
	int	k;
	char	*output;

	i = 0;
	k = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	output = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	while (str[i] != '\0')
		output[k++] = str[i++];
	output[k] = '\0';
	return (output);
}
