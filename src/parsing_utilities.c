/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:23:17 by aharder           #+#    #+#             */
/*   Updated: 2025/02/19 15:24:42 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
char	**another_custom_split(char *s, char c)
{
	int	i[5];
	char	**output;

	i[0] = 0;
	i[2] = 0;
	i[4] = 0;
	output = malloc((splitlen(s) + 1) * sizeof(char *));
	if (!output)
		return NULL;
	while (s[i[0]] != '\0')
	{
		while (s[i[0]] == c)
			i[0]++;
		if (s[i[0]] == '\0')
			break;
		i[1] = i[0];
		if (s[i[1]] == '"' || s[i[1]] == '\'')
		{
			i[4] = s[i[1]];
			i[1]++;
			while (s[i[1]] != i[4] && s[i[1]] != '\0')
				i[1]++;
			if (s[i[1]] != i[4])
			{
			printf("Error: bracket\n");
			return NULL;
			}
			else
				i[1]++;
		}
		else
		{
			while (s[i[1]] != c && s[i[1]] != '\'' && s[i[1]] != '"' && s[i[1]] != '\0')
			i[1]++;
		}
		output[i[2]] = malloc((i[1] - i[0] + 1) * sizeof(char));
		if (!output[i[2]])
			return NULL;
		i[3] = 0;
		while (i[0] < i[1])
			output[i[2]][i[3]++] = s[i[0]++];
		output[i[2]][i[3]] = '\0';
		i[2]++;
	}
	output[i[2]] = NULL;
	return (output);
}*/

int	array_size(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void print_commands(t_commands *commands)
{
	t_commands *current = commands;
	while (current != NULL)
	{
		printf("Pipe Type: %d\n", current->pipe_type);
		for (int i = 0; current->command[i] != NULL; i++)
		{
			printf("Command[%d]: %s\n", i, current->command[i]);
		}
		current = current->next;
	}
}

void print_redirection(t_io_red *redirection)
{
	t_io_red *current = redirection;
	while (current != NULL)
	{
		printf("IO Type: %d\n", current->in_or_out);
		printf("File: %s\n", current->file);
		current = current->next;
	}
}

int splitlen(char *s, char c)
{
    int i;
    int count;
    int in_segment;
    char quote;

    i = 0;
    count = 0;
    in_segment = 0;
    while (s[i] != '\0')
    {
        if ((s[i] == '"' || s[i] == '\'') && !in_segment)
        {
            quote = s[i];
            i++;
            while (s[i] != quote && s[i] != '\0')
                i++;
            if (s[i] == quote)
                i++;
            in_segment = 1;
            count++;
        }
        else if (s[i] != c && !in_segment)
        {
            in_segment = 1;
            count++;
        }
        else if (s[i] == c)
            in_segment = 0;
        i++;
    }
    return count;
}

int	cmp(char c)
{
	int	i;
	char	list[] = { '|', '<', '>', '\0' };

	i = 0;
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
}
