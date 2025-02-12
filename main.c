/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:54 by aharder           #+#    #+#             */
/*   Updated: 2025/02/12 22:11:26 by aharder          ###   ########.fr       */
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
	}
	return (-1);
}
void	add_command(t_command **a, char **args)
{
	t_command	*buffer;
	t_command	*last;

	buffer = malloc(sizeof(t_stack));
	buffer->size = ;
	buffer->command = 
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
}

typedef	struct	s_command
{
	int	size;
	char	*command;
	struct s_command	*next;
}	t_command;

int	parse_command_line(char *str)
{
	int	i;
	char	**args;
	t_command	*command;
	args = ft_split(str, " ");
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strlstcmp(args[i], commands)
			command = add_command(&args[i]);
	}
	
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
		if (ft_strcmp(minishell, "clear") == 0)
			clear();
		if (ft_strcmp(minishell, "exit") == 0)
		{
			free(minishell);
			break;
		}
	}
}
