/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:35 by aharder           #+#    #+#             */
/*   Updated: 2025/02/19 14:39:05 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		sizestr;
	int		i;

	sizestr = ft_strlen(src);
	dest = malloc((sizestr + 1) * sizeof(*dest));
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
/*
typedef struct	s_commands
{
	char	*type;
	int	i;
	char	*command;
}	t_commands;
*/
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
	pipetype    pipe_type;
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

void	add_command(t_commands **a, char *splitted, pipetype type)
{
	t_commands	*buffer;
	t_commands	*last;

	buffer = malloc(sizeof(t_commands));
	buffer->pipe_type = type;
	buffer->command = another_custom_split(splitted, ' ');
	buffer->next = NULL;
	if (*a)
		*a = buffer;
	else
	{
		last = *a;
		while (last->next)
			last = last->next;
		last->next = buffer;
	}
}

int	array_size(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
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
	if(!a)
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
	if (*a)
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

void	putlist(t_commands **commands, t_io_red **redirection, char **splitted, char *operator)
{
	char	*buffer;
	int	i;

	i = 0;
	while (splitted[i] != NULL)
	{
		if (operator[i] == '|')
			add_command(commands, splitted[i], PIPE);
		if (operator[i] == '<')
		{
			buffer = add_io(redirection, splitted[i], INPUT);
			add_buff_to_last(commands, buffer);
		}
		if (operator[i] == '>')
		{
			buffer = add_io(redirection, splitted[i], OUTPUT);
			add_buff_to_last(commands, buffer);
		}
		i++;
	} 
}
int	main(int argc, char *argv[])
{
	int	i;
	char	**splitted;
	char	*operator;
	t_commands	*commands;
	t_io_red	*redirection;
	if (argc < 2)
		return (printf("Erreur: input\n"));
	i = 0;
	splitted = multi_split(argv[1]);
	operator = get_operators(argv[1]);
	putlist(&commands, &redirection, splitted, operator);
	free_split(splitted);
	free(operator);
}
