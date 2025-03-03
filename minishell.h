/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:20:28 by aharder           #+#    #+#             */
/*   Updated: 2025/02/19 14:29:44 by paraponerashinji ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>

typedef struct s_command
{
    int size;
    char *command;
    struct s_command *next;
} t_command;

typedef enum {
    PIPE,
    OR_PIPE,
    IF_PIPE,
    INPUT_DEL,
    SIMPLE_INPUT,
    OUTPUT_APP,
    SIMPLE_OUTPUT,
    ERROR
}	type;

typedef enum {
    INPUT,
    OUTPUT
} iotype;

typedef struct s_commands
{
    int pipe_type;
    char **command;
    struct s_commands *next;
} t_commands;

typedef struct s_io_red
{
    int in_or_out;
    char *file;
    struct s_io_red *next;	
} t_io_red;

// Déclaration des fonctions
void handle_signal(int sig);
char *get_prompt();
void cd_command(char *input);
void clear();
int ft_strlstcmp(char *str, char **list, int size);
int parse_command_line(char *str, char **envp);
void free_split(char **split);
int checkargs(int argc);
char *ft_getenv(char *name, char **env);
char *get_path(char *cmd, char **env);
int executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp);
int createpipes(t_commands *commands, t_io_red *redirection, char **envp);

int cmp(char c);
int splitlen2(const char *s, char c);
int splitlen(char *s, char c);
char **multi_split(char *s);
int *get_operators(char *s);
char **another_custom_split(char *s, char c);
char *first_word(char *str);
char *rm_first_word(char *str);
void add_command(t_commands **a, char *splitted, int op);
int array_size(char **arr);
void add_buff_to_last(t_commands **a, char *str);
char    *ft_replacesubstr(char  *str, char *to_replace, char *replacement);
char *add_io(t_io_red **a, char *splitted, int type);
void putlist(t_commands **commands, t_io_red **redirection, char **splitted, int *operator);
void print_commands(t_commands *commands);
void print_redirection(t_io_red *redirection);
void	parser(char *str, char **envp);
char    **first_split(char *s);
char    **second_split(char *s, char c);

#endif // MINISHELL_H
