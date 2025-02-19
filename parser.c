/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:35 by aharder           #+#    #+#             */
/*   Updated: 2025/02/19 13:53:00 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

typedef struct	s_commands
{
	char	*type;
	int	i;
	char	*command;
}	t_commands;

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

int	splitlen2(const char *s, char c)
{
	int	i;
	int	split;

	i = 0;
	split = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			split++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (split);
}

int	splitlen(const char *s)
{
	int	i;
	int	split;

	i = 0;
	split = 0;
	while (s[i] != '\0')
	{
		while (cmp(s[i]) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			split++;
		while (!cmp(s[i]) && s[i] != '\0')
			i++;
	}
	return (split);
}

char	**multi_split(char *s)
{
	int	i[5];
	int	buffer;
	char	**output;

	i[0] = 0;
	i[2] = 0;
	i[4] = 0;
	output = malloc((splitlen(s) + 1) * sizeof(char *));
	if (!output)
		return NULL;
	while (s[i[0]] != '\0')
	{
		if (cmp(s[i[0]]) == 1 && s[i[0]] != '\0')
		{
			if (s[i[0]] == '"')
				i[4] = !i[4];
			i[0]++;
		}
		if (cmp(s[i[0]]) == 1 && s[i[0]] != '\0')
			return NULL;
		if (s[i[0]] == '\0')
			break;
		i[1] = i[0];
		while ((cmp(s[i[1]]) == 0 || i[4]) && s[i[1]] != '\0')
		{
			if (s[i[1]] == '"')
				i[4] = !i[4];
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
	if (i[4])
	{
		printf("Error: bracket\n");
		return NULL;
	}
	output[i[2]] = NULL;
	return (output);
}

char	*get_operators(char *s)
{
	int	i[2];
	int	quotes;
	char	*output;

	i[0] = 0;
	i[1] = 0;
	quotes = 0;
	output = malloc((splitlen(s) * 2 + 2) * sizeof(char));
	output[i[1]++] = '|';
	if (!output)
		return NULL;
	while (s[i[0]] != '\0')
	{
		if (cmp(s[i[0]]) == 1)
		{
			if (!quotes)
				output[i[1]++] = s[i[0]];
		}
		else if (s[i[0]] == '"')
		{
			quotes = !quotes;
		}
		i[0]++;
	}
	output[i[1]] = '\0';
	return (output);
}

typedef enum {
	PIPE,
	OR_PIPE,
	IF_PIPE
}	pipetype;

typedef enum {
	INPUT,
	OUTPUT
}	iotype;

typedef struct  s_commands
{
	pipetype    *pipe_type;
	char    **command;
	struct s_commands	*next;
}       t_commands;

typedef struct s_io_red
{
	iotype	in_or_out;
	char	*file;
	struct s_io_red	*next;	
}	t_io_red;

char	**another_custom_split(char *s, char c)
{
	int	i[5];
	int	buffer;
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
		{
			if (s[i[0]] == '"')
				i[4] = !i[4];
			i[0]++;
		}
		if (s[i[0]] == '\0')
			break;
		i[1] = i[0];
		while ((s[i[1]] != c || i[4]) && s[i[1]] != '\0')
		{
			if (s[i[1]] == '"')
				i[4] = !i[4];
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
	if (i[4])
	{
		printf("Error: bracket\n");
		return NULL;
	}
	output[i[2]] = NULL;
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
		output[k++] = str[i];
	}
	output[k] = '\0';
	return (output);
}

char	rm_first_word(char *str)
{
	int	i;
	int	k;
	char	*output;

	i = 0;
	k = 0;
	while (str[i] == ' ')
		i++;
	while (str != ' ' && str[i] != '\0')
		i++;
	output = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	while (str[i] != '\0')
		output[k++] = str[i++];
	output[k] = '\0';
	return (output);
}

void	add_command(t_commands **a, char *splitted, pipetype type)
{
	t_commands	*buffer;
	t_commands	*last;

	buffer = malloc(sizeof(t_commands));
	buffer->pipe_type = type;
	buffer->command = another_custom_split(splitted, " ");
	buffer->next = NULL;
	if (*a)
		a = buffer;
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

	i = 0;
	if(!a)
	{
		buffer = malloc(sizeof(t_commands));
		buffer->pipe_type = PIPE;
		buffer->command = another_custom_split(str, " ");
		buffer->next = NULL;
		a = buffer; 
	}
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		
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
	if (*a)
		a = buffer;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = buffer;
	}
	return (output);
}

t_commands	putlist(char **splitted, char *op<F12erator, int size)
{
	t_commands	*commands;
	t_io_red	*redirection;
	char	*buffer;
	int	i;

	i = 0;
	while (splitted[i] != NULL)
	{
		if (operator[i] == '|')
			add_command(&commands, splitted[i], PIPE);
		if (operator[i] == '<')
		{
			buffer = add_io(&redirection, splitted[i], INPUT);
			add_buff_to_last(&commands, buffer);
		}
		if (operator[i] == '>')
		{
			buffer = add_io(&redirection, splitted[i], OUTPUT);
			add_buff_to_last(&commands, buffer);
		}
	} 
}
int	main(int argc, char *argv[])
{
	int	i;
	char	**splitted;
	char	*operator;
	t_commands	*commands;
	if (argc < 2)
		return (printf("Erreur: input\n"));
	i = 0;
	splitted = multi_split(argv[1]);
	operator = get_operators(argv[1]);
	commands = malloc(splitlen((argv[1]) + 2) * sizeof(t_commands));
	if (splitted == NULL)
		return (0);
	while (splitted[i] != NULL)
	{
		commands[i].type = malloc(6 * sizeof(char));
		commands[i].command = malloc(strlen(splitted[i]) + 1);
		commands[i].i = 1;
		strcpy(commands[i].command, splitted[i]);
		if (operator[i] == '|')
			strcpy(commands[i].type, "PIPE");
		else if (operator[i] == '<')
			strcpy(commands[i].type, "I_RED");
		else if (operator[i] == '>')
			strcpy(commands[i].type, "O_RED");
		i++;
	}
	commands[i].commands = NULL;
	commands[i].type = NULL;
	commands[i].i = -1;
	i = 0;
	while (commands[i].i != -1)
	{
		printf("Operator:\n%s\nCommand:\n%s\n", commands[i].type, commands[i].command);
		i++;
	}
	free_split(splitted);
	free(operator);
}
