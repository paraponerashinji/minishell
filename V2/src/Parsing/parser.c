/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:20:16 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 00:11:16 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(char *str)
{
	char		**splitted;
	int			*operator;
	t_commands	*commands;
	t_io_red	*redirection;

	commands = NULL;
	redirection = NULL;
	splitted = first_split(str);
	operator = get_operators(str);
	putlist(&commands, &redirection, splitted, operator);
	print_commands(commands);
	print_redirection(redirection);
	if (valid_line(commands, redirection) == 0)
		createpipes(commands, redirection);
	free_red(&redirection);
	free_cmd(&commands);
	free_split(splitted);
	free(operator);
}

void	putlist(t_commands **cmds, t_io_red **red, char **split, int *op)
{
	char	*buffer;
	int		i;

	i = 0;
	while (split[i] != NULL)
	{
		if (op[i] == 2)
			add_command(cmds, split[i], 2);
		else if (op[i] == 1)
			add_command(cmds, split[i], 1);
		else if (op[i] == 3)
		{
			add_command(cmds, split[i], 3);
		}
		else if (op[i] != 0)
		{
			buffer = add_io(red, split[i], op[i]);
			add_buff_to_last(cmds, buffer);
		}
		else
			printf("ERREUR OPERATEUR");
		i++;
	}
}

int	*get_operators(char *s)
{
	int	i[4];
	int	*output;

	i[0] = 0;
	i[1] = 1;
	i[2] = 0;
	i[3] = splitlen(s, ' ');
	output = malloc((splitlen(s, ' ') + 1) * sizeof(int));
	if (!output)
		return (NULL);
	output[0] = 2;
	while (s[i[0]] != '\0')
	{
		if ((cmp(s[i[0]]) == 1) && !i[2])
			handle_operator(s, &i[0], &i[1], output);
		else if (s[i[0]] == '"')
			i[2] = !i[2];
		i[0]++;
		if (i[1] > i[3])
			return (output);
	}
	output[i[1]] = '\0';
	return (output);
}

void	print_commands(t_commands *commands)
{
	t_commands	*current;
	int			i;

	i = 0;
	current = commands;
	while (current != NULL)
	{
		printf("Pipe Type: %d\n", current->pipe_type);
		while (current->command[i] != NULL)
		{
			printf("Command[%d]: %s\n", i, current->command[i]);
			i++;
		}
		current = current->next;
	}
}

void	print_redirection(t_io_red *redirection)
{
	t_io_red	*current;

	current = redirection;
	while (current != NULL)
	{
		printf("IO Type: %d\n", current->in_or_out);
		printf("File: %s\n", current->file);
		current = current->next;
	}
}
