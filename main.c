/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:54 by aharder           #+#    #+#             */
/*   Updated: 2025/02/27 17:39:22 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*crop_path(char **path)
{
	int	i;
	char	*buffer;
	char	*buffer2;

	i = 0;
	while (path[i] != NULL)
		i++;
	buffer = ft_strjoin(path[i-2], "/");
	buffer2 = ft_strjoin(buffer, path[i-1]);
	free(buffer);
	return (buffer2);
}

char	*get_prompt()
{
	char	path[1024];
	char	*buffer;
	char	**buffer2;
	char	*prompt = NULL;
	char	*prefix = "\e[1;32mminishell\e[0m:\e[1;34m~/";
	char	*suffix = "\e[0m ";

	if (getcwd(path, sizeof(path)) != NULL)
	{
		buffer2 = ft_split(path, '/');
		prompt = crop_path(buffer2);
		free_split(buffer2);
		buffer = ft_strjoin(prefix, prompt);
		free(prompt);
		prompt = ft_strjoin(buffer, suffix);
		free(buffer);
	}
	return (prompt);
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

void	print_mini()
{
	printf(" __  __ ___ _   _ ___ ____  _   _ _____ _     _     \n");
	printf("|  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |    \n");
	printf("| |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |    \n");
	printf("| |  | || || |\\  || | ___) |  _  | |___| |___| |___ \n");
	printf("|_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|\n\n");
}
int	main(int argc, char **argv, char **envp)
{
	char	*minishell;
	char	*prompt;

	(void)argc;
	(void)argv;
	(void)envp;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	printf("\e[H\e[J");
	print_mini();
	while (1)
	{
		prompt = get_prompt();
		minishell = readline(prompt);
		free(prompt);
		if (minishell == NULL)
		{
			free(minishell);
			break;
		}
		add_history(minishell);
		parser(minishell, envp);
		if (ft_strcmp(minishell, "exit") == 0)
		{
			rl_clear_history();
			free(minishell);
			break;
		}
		free(minishell);
	}
}
