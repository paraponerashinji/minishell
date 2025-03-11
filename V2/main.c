/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:27:04 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 13:26:02 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	int		i;
	char	*buffer;
	char	*buffer2;

	i = 0;
	while (path[i] != NULL)
		i++;
	buffer = ft_strjoin(path[i - 2], "/");
	buffer2 = ft_strjoin(buffer, path[i - 1]);
	free(buffer);
	return (buffer2);
}

char	*get_prompt(void)
{
	char	path[1024];
	char	*buffer;
	char	**buffer2;
	char	*prompt = NULL;
	char	*prefix = "\e[1;32mminishell\e[0m:\e[1;34m~/";
	char	*suffix = "\e[0m";

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

void	print_mini(void)
{
	printf("___  ________ _   _ _____ _____ _   _  _____ _      _     \n");
	printf("|  \\/  |_   _| \\ | |_   _/  ___| | | ||  ___| |    | |    \n");
	printf("| .  . | | | |  \\| | | | \\ `--.| |_| || |__ | |    | |    \n");
	printf("| |\\/| | | | | . ` | | |  `--. \\  _  ||  __|| |    | |    \n");
	printf("| |  | |_| |_| |\\  |_| |_/\\__/ / | | || |___| |____| |____\n");
	printf("\\_|  |_/\\___/\\_| \\_/\\___/");
	printf("\\____/\\_| |_/\\____/\\_____/\\_____/\n");
}

int	main(int argc, char **argv, char **envp)
{
	char		*minishell;
	char		*prompt;
	t_mini		mini;

	(void)argc;
	(void)argv;
	mini.commands = NULL;
	mini.redirection = NULL;
	mini.env = init_env(envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	printf("\e[H\e[J");
	print_mini();
	while (1)
	{
		prompt = get_prompt();
		printf("%s", prompt);
		minishell = readline(">");
		free(prompt);
		if (minishell == NULL)
		{
			printf("Readline returned NULL\n");
			free(minishell);
			break ;
		}
		add_history(minishell);
		parser(minishell, &mini);
		free(minishell);
	}
	free_env(mini.env);
}
