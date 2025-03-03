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

#include ".../include/minishell.h"

void	parser(char *str)
{
	char		**splitted;
	char		*operator;
	t_commands	*commands;
	t_io_red	*redirection;

	splitted = first_split(str);
	operator = get_operators(str);
	putlist(&commands, &redirection, splitted, operator);
	print_commands(commands);
	print_redirection(redirection);
	createpipes(commands, redirection, envp);
	free_split(splitted);
	free(operator);
}

void	putlist(t_commands **commands,
		t_io_red **redirection, char **splitted, char *operator)
{
	char	*buffer;
	int		i;

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
