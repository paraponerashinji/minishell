/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:15:12 by aharder           #+#    #+#             */
/*   Updated: 2025/02/21 17:24:04 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**multi_split(char *s)
{
	int	i[6];
	char	**output;

	i[0] = 0;
	i[2] = 0;
	i[4] = 0;
	i[5] = 0;
	output = malloc((splitlen(s) + 1) * sizeof(char *));
	if (!output)
		return NULL;
	while (s[i[0]] != '\0')
	{
		if (cmp(s[i[0]]) == 1 && s[i[0]] != '\0')
		{
			if (s[i[0]] == '"')
				i[4] = !i[4];
			else if (s[i[0]] == '\'')
				i[5] = !i[5];
			i[0]++;
		}
		if (cmp(s[i[0]]) == 1 && s[i[0]] != '\0')
			return NULL;
		if (s[i[0]] == '\0')
			break;
		i[1] = i[0];
		while ((cmp(s[i[1]]) == 0 || i[4] || i[5]) && s[i[1]] != '\0')
		{
			if (!i[5] && s[i[1]] == '"')
				i[4] = !i[4];
			else if (!i[4] && s[i[1]] == '\'')
				i[5] = !i[5];
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

void	parser(char *str, char **envp)
{
	char	**splitted;
	char	*operator;
	t_commands	*commands = NULL;
	t_io_red	*redirection = NULL;

	splitted = multi_split(str);
	operator = get_operators(str);
	putlist(&commands, &redirection, splitted, operator);
	print_commands(commands);
	print_redirection(redirection);
	createpipes(commands, redirection, envp);
	free_split(splitted);
	free(operator);
}
