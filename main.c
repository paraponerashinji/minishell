/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:54 by aharder           #+#    #+#             */
/*   Updated: 2025/02/13 18:21:36 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"

void	handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

char	*get_prompt()
{
	char	path[1024];
	char	*buffer;
	char	*prompt;
	char	*prefix = "\e[1;32mminishell\e[0m: \e[1;34m";
	char	*suffix = ">\e[0m ";

	if (getcwd(path, sizeof(path)) != NULL)
	{
		buffer = ft_strjoin(prefix, path);
		prompt = ft_strjoin(buffer, suffix);
		free(buffer);
	}
	return (prompt);
}

void	cd_command(char *input)
{
	ft_printf("TODO : %s\n", input);
}

void	clear()
{
	ft_printf("\e[H\e[J");
	rl_clear_history();
}

int	ft_strlstcmp(char *str, char **list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(str, list[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

typedef struct	s_command
{
	int	size;
	char	*command;
	struct s_command	*next;
}	t_command;

int	add_command(t_command **a, char **args)
{
	t_command	*buffer;
	t_command	*last;
	char	*ends[] = {"|", "&&", "||"};
	int	i;

	buffer = malloc(sizeof(t_command));
	buffer->command = args[0];
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strlstcmp(args[i], ends, 3) == -1)
		{
			buffer->command = ft_strjoin(buffer->command, " ");
			buffer->command = ft_strjoin(buffer->command, args[i]);
		}
		else
			break;
		i++;
	}
	buffer->size = i;
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
	return (i);
}

void	print_commands(t_command *commands)
{
	t_command	*temp;

	temp = commands;
	while (temp != NULL)
	{
		ft_printf("Command: %s\n", temp->command);
		temp = temp->next;
	}
}

int	parse_command_line(char *str)
{
	int	i;
	char	**args;
	t_command	*command;
	char	*commands[] = {"cd", "echo", "exit", "clear"};
	args = ft_split(str, ' ');
	i = 0;
	command = NULL;
	while (args[i] != NULL)
	{
		if (ft_strlstcmp(args[i], commands, 4) != -1)
			i += add_command(&command, &args[i]);
		else
			i++;
	}
	print_commands(command);
	return (0);
}
int	main()
{
	char	*minishell;
	char	*prompt;

	signal(SIGINT, handle_signal);
	ft_printf("\e[H\e[J");
	while (1)
	{
		prompt = get_prompt();
		minishell = readline(prompt);
		free(prompt);
		parse_command_line(minishell);
		if (ft_strcmp(minishell, "exit") == 0)
		{
			free(minishell);
			break;
		}
	}
}