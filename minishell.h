/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:20:28 by aharder           #+#    #+#             */
/*   Updated: 2025/02/15 14:14:26 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "libft/libft.h" // Inclusion de la libft
#include <sys/wait.h>

typedef struct	s_command
{
	int	size;
	char	*command;
	struct s_command	*next;
}	t_command;

void handle_signal(int sig);
char *get_prompt();
void cd_command(char *input);
void clear();
int ft_strlstcmp(char *str, char **list, int size);
int add_command(t_command **a, char **args);
void print_commands(t_command *commands);
int     parse_command_line(char *str, char **envp);
void free_split(char **split);
int checkargs(int argc);
char *ft_getenv(char *name, char **env);
char *get_path(char *cmd, char **env);
void executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp);
int createpipes(t_command *commands, char **envp);

#endif // MINISHELL_H
