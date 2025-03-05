/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:16 by aharder           #+#    #+#             */
/*   Updated: 2025/02/26 18:24:08 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(char *str)
{
	char		**splitted;
	int		*operator;
	t_commands	*commands = NULL;
	t_io_red	*redirection = NULL;

	splitted = first_split(str);
	operator = get_operators(str);
	putlist(&commands, &redirection, splitted, operator);
	print_commands(commands);
	print_redirection(redirection);
	//createpipes(commands, redirection);
	free_split(splitted);
	free(operator);
}

void	putlist(t_commands **commands, t_io_red **redirection, char **splitted, int *operator)
{
	char	*buffer;
	int	i;

	i = 0;
	while (splitted[i] != NULL)
	{
		if (operator[i] == 2)
			add_command(commands, splitted[i], 2);
		else if (operator[i] == 1)
			add_command(commands, splitted[i], 1);
		else if (operator[i] == 3)
		{
			add_command(commands, splitted[i], 3);
		}
		else if (operator[i] != 0)
		{
			buffer = add_io(redirection, splitted[i], operator[i]);
			add_buff_to_last(commands, buffer);
		}
		else
			printf("ERREUR OPERATEUR");
		i++;
	} 
}

int	*get_operators(char *s)
{
	int	i[2];
	int	quotes;
	int	*output;

	i[0] = 0;
	i[1] = 0;
	quotes = 0;
	output = malloc((splitlen(s, ' ') * 2 + 2) * sizeof(int));
	if (!output)
		return NULL;
	output[i[1]++] = 2;
	while (s[i[0]] != '\0')
	{
		if ((cmp(s[i[0]]) == 1) && !quotes)
		{
			output[i[1]] = find_op(&s[i[0]++]);
			if (output[i[1]] == 1 || output[i[1]] == 3 || output[i[1]] == 4 || output[i[1]] == 6)
				i[0]++;
			i[1]++;
		}
		else if (s[i[0]] == '"')
			quotes = !quotes;
		i[0]++;
	}
	output[i[1]] = '\0';
	return (output);
}

int	cmp(char c)
{
	int	i;
	char	list[] = { '|', '<', '>', '&', '\0'};

	i = 0;
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
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

int	find_op(char *s)
{
	if (s[0] == '|' &&  s[1] == '|')
		return (1);
	else if (s[0] == '|')
		return (2);
	else if (s[0] == '&' && s[1] == '&')
		return (3);
	else if (s[0] == '<' && s[1] == '<')
		return (4);
	else if (s[0] == '<')
		return (5);
	else if (s[0] == '>' && s[1] == '>')
		return (6);
	else if (s[0] == '>')
		return (7);
	else
		return (0);
}

int	array_size(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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