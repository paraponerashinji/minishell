/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:57:54 by aharder           #+#    #+#             */
/*   Updated: 2025/02/17 12:46:14 by aharder          ###   ########.fr       */
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

int	parse_command_line(char *str, char **envp)
{
	int	i;
	char	**args;
	t_command	*command;
	char	*commands[] = {"cd", "echo", "exit", "pwd", "export", "unset", "env"};
	args = ft_split(str, ' ');
	i = 0;
	command = NULL;
	while (args[i] != NULL)
	{
		if (ft_strlstcmp(args[i], commands, 7) != -1)
			i += add_command(&command, &args[i]);
		else
			i++;
	}
	createpipes(command, envp);
	print_commands(command);
	return (0);
}

void	execute(char *cmd, char **envp)
{
	pid_t	p;
	char	path[1024];
	char	*full_cmd;
	char	**args;

	args = NULL;
	(void)cmd;
	p = fork();
	if (p == 0)
	{
		getcwd(path, sizeof(path));
		full_cmd = ft_strjoin(path, "/src/cmds/pwd");
		execve(full_cmd, args, envp);
		free(full_cmd);
		exit(1);
	}
	else if (p == -1)
		printf("fork error");
	else
		waitpid(p, NULL, 0);
}
int	main(int argc, char **argv, char **envp)
{
	char	*minishell;
	char	*prompt;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	ft_printf("\e[H\e[J");
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
		if (ft_strcmp(minishell, "pwd") ==  0)
			execute("pwd", envp);
		//parse_command_line(minishell, envp);
		if (ft_strcmp(minishell, "exit") == 0)
		{
			rl_clear_history();
			free(minishell);
			break;
		}
	}
}
