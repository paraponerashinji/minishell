/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:54 by aharder           #+#    #+#             */
/*   Updated: 2025/02/12 18:08:45 by aharder          ###   ########.fr       */
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

void	add_to_stack(t_stack **a, int value)
{
	t_stack	*buffer;
	t_stack	*last;

	buffer = malloc(sizeof(t_stack));
	buffer->stack = value;
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
	
	args = ft_split(str, " ");
	i = 0;
	while (args[i] != NULL)
	{
		if (is_command(args[i])
			get_args(&args[i]);
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
