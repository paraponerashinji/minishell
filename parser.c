/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:35 by aharder           #+#    #+#             */
/*   Updated: 2025/02/18 13:18:08 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

typedef enum
{
	PIPE,
	I_RED,
	O_RED,
	AND_PIPE,
	OR_PIPE
}	command_type;

typedef struct	s_commands
{
	command_type	type;
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
int	main(int argc, char *argv[])
{
	int	i;
	char	**splitted;
	char	*operator;
	t_commands	commands;
	if (argc < 2)
		return (printf("Erreur: input\n"));
	i = 0;
	splitted = multi_split(argv[1]);
	operator = get_operators(argv[1]);
	if (splitted == NULL)
		return (0);
	while (splitted[i] != NULL)
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	printf("%s\n", operator);
	free_split(splitted);
	free(operator);
}
