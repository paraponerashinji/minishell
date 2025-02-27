/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:15:12 by aharder           #+#    #+#             */
/*   Updated: 2025/02/27 01:39:47 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			output[i[1]++] = find_op(&s[i[0]++]);
			if (output[i[1]] == 1 || output[i[1]] == 3 || output[i[1]] == 4 || output[i[1]] == 6)
				i[0]++;
		}
		else if (s[i[0]] == '"')
			quotes = !quotes;
		i[0]++;
	}
	output[i[1]] = '\0';
	return (output);
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
			printf("hey");
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

void	free_cmd(t_commands **a)
{
	t_commands	*tmp;
	int	i;

	i = 0;
	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		while (tmp->command[i] != NULL)
			free(tmp->command[i++]);
		free(tmp->command);
		free(tmp);
	}
}

void	free_red(t_io_red **a)
{
	t_io_red	*tmp;

	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		free(tmp->file);
		free(tmp);
	}
}

void	parser(char *str, char **envp)
{
	char	**splitted;
	int	*operator;
	t_commands	*commands = NULL;
	t_io_red	*redirection = NULL;

	splitted = first_split(str);
	operator = get_operators(str);
	putlist(&commands, &redirection, splitted, operator);
	print_commands(commands);
	print_redirection(redirection);
	createpipes(commands, redirection, envp);
	free_cmd(&commands);
	free_red(&redirection);
	free_split(splitted);
	free(operator);
}
