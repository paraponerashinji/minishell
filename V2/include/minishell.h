/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:23:49 by aharder           #+#    #+#             */
/*   Updated: 2025/03/03 14:34:49 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <libgen.h>

typedef struct s_commands
{
	int					pipe_type;
	char				**command;
	struct s_commands	*next;
}	t_commands;

typedef struct s_commands
{
	int				in_or_out;
	char			**command;
	struct s_io_red	*next;
}	t_io_red;

// MAIN
char		*get_prompt(void);
char		*crop_path(char **path);
void		handle_signal(int sig);
void		handle_signal(int sig);
// PARSING
void		parser(char *str, char **envp);
int			splitlen(char *s, char c);
int			*get_operators(char *s);
int			find_op(char *s);
void		putlist(t_commands **cmds, t_io_red **red, char **split, int *op);
void		add_command(t_commands **a, char *splitted, int op);
t_commands	*init_command_node(char **command);
t_commands	*get_last_command(t_commands *a);
char		**merge_command(char **old, char **to_add);
void		add_buff_to_last(t_commands **a, char *str);
char		*first_word(char *str);
char		*rm_first_word(char *str);
char		*add_io(t_io_red **a, char *splitted, int op);
void		free_cmd(t_commands **a);
void		free_red(t_io_red **a);
// FIRST SPLIT
char		**first_split(char *s);
void		assign_start_value(t_var_bundle *var);
int			first_split_size(char *s);
void		process_string(char *s, t_var_bundle *var, char **output);
char		*crop_str(char *s, int start, int end);
int			srch_operator(char *s);
void		handle_quotes(t_var_bundle *var, char c);
char		**perror_and_free(char **output);
// SECOND SPLIT
char		**second_split(char *s, char c);
char		*write_segment(char *s, int start, int end);
int			find_segment_end(char *s, char c, int start);
// PIPES
int			createpipes(t_commands *commands, t_io_red *redirection, char **envp);
int			is_command(char	*str);
int			executefile(char *cmd, char **args, int i_fd, int o_fd, char **envp);
int			executecommand(char *cmd, char **args, int i_fd, int o_fd, char **envp);
// INPUT REDIRECTION, ENV VAR AND *
int			find_i_red(t_io_red *redirection);
void		get_heredoc(int *p_fd, char *end);
void		check_env(t_commands *temp);
char		**insert_files(char **command, int index);
char		**get_filenames(void);
int			ft_strchrpos(char *str, int searchedChar);
// OUTPUT REDIRECTION
void		write_output(int buff_fd, t_io_red *redirection);
void		copy(int buff_fd, int *o_fd, int size);
void		copy_single(int buff_fd, int o_fd);
void		free_and_close(int *fd, int size);

// UTILITIES
void		free_split(char **split);
#endif
