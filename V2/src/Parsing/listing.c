/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:27:22 by aharder           #+#    #+#             */
/*   Updated: 2025/02/26 18:49:43 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..../include/minishell.h"

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

void	add_buff_to_last(t_commands **a, char *str)
{
	t_commands	*buffer;
	t_commands	*last;
	char		**buffer_split;
	char		**new_command;

	buffer_split = second_split(str, ' ');
	if (!*a)
		*a = init_command_node(buffer_split);
	else
	{
		get_last_command(*a);
		new_command = merge_command(last->command, buffer_split);
		free(last->command);
		last->command = new_command;
	}
}

char	*first_word(char *str)
{
	int		i;
	int		k;
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
	int		i;
	int		k;
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
