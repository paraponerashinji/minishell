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
	buffer->command = another_custom_split(splitted, ' ');
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

void	add_buff_to_last(t_commands **a, char *str)
{
	t_commands	*buffer;
	t_commands	*last;
	int	i;
	int	old_size;
	int	add_size;
	int	new_size;
	char	**buffer_array;
	char	**buffer_split;

	buffer_split = another_custom_split(str, ' ');
	add_size = array_size(buffer_split);
	i = 0;
	if(!*a)
	{
		buffer = malloc(sizeof(t_commands));
		buffer->pipe_type = PIPE;
		buffer->command = buffer_split;
		buffer->next = NULL;
		*a = buffer; 
	}
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		old_size = array_size(last->command);
		new_size = old_size + add_size;
		buffer_array = malloc((new_size + 1) * sizeof(char*));
		while (last->command[i] != NULL)
		{
			buffer_array[i] = ft_strdup(last->command[i]);
			i++;
		}
		old_size = 0;
		while (buffer_split[old_size] != NULL)
			buffer_array[i++] = ft_strdup(buffer_split[old_size++]);
		last->command = buffer_array;
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
