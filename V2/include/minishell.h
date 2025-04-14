/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:23:49 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 14:29:28 by aharder          ###   ########.fr       */
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
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <libgen.h>
# include "get_next_line.h"

typedef struct s_env
{
	char			*value;
	char			*result;
	struct s_env	*next;
}	t_env;

typedef struct s_commands
{
	int					pipe_type;
	char				**command;
	struct s_commands	*next;
}	t_commands;

typedef struct s_io_red
{
	int				in_or_out;
	char			*file;
	struct s_io_red	*next;
}	t_io_red;

typedef struct s_mini
{
	struct s_io_red		*redirection;
	struct s_env		*env;
	struct s_commands	*commands;
}	t_mini;

typedef struct s_var_bundle
{
	int	i;
	int	j;
	int	y;
	int	s_quotes;
	int	d_quotes;
}	t_var_bundle;

typedef struct s_var_env_bundle
{
	int	i;
	int	j;
	int	k;
	int	s_quotes;
	int	d_quotes;
}	t_var_env_bundle;

// MAIN
char		*get_prompt(void);
char		*crop_path(char **path);
void		handle_signal(int sig);
void		handle_signal(int sig);
// PARSING
void		parser(char *str, t_mini *mini);
int			splitlen(char *s, char c);
int			*get_operators(char *s);
int			find_op(char *s);
int			splitlen(char *s, char c);
int			cmp(char c);
int			handle_quotes_bis(char *s, int i);
int			handle_operator(char *s, int *i, int *j, int *output);
void		init_list(char *list);
// ENV
void		add_first_command(t_commands **a, char *s, char **envp);
t_env		*init_env(char **envp);
void		add_env(t_env **a, char *value, char *result);
void		free_env(t_env *env);
// LISTING
int			putlist(t_mini *mini, char **split, int *op);
void		add_command(t_commands **a, char *splitted, int op);
t_commands	*init_command_node(char **command);
t_commands	*get_last_command(t_commands *a);
char		**merge_command(char **old, char **to_add);
void		add_buff_to_last(t_commands **a, char *str);
char		*first_word(char *str);
char		*rm_first_word(char *str);
char		*add_io(t_io_red **a, char *splitted, int type, t_mini *mini);
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
char		**perror_and_free(char **output, int size);
// SECOND SPLIT
char		**second_split(char *s, char c);
char		*write_segment(char *s, int start, int end);
int			find_segment_end(char *s, char c, int start);
// VALID LINES
int			valid_line(t_commands *cmd, t_io_red *red);
int			print_pipe_error(void);
// PIPES
int			createpipes(t_commands *cmds, t_io_red *red, t_env *env);
void		process_commands(t_commands *cmds, t_env *env, int b_fd[2], int b);
void		init_pipes(int p_fd[2], int b_fd[2]);
void		close_pipes(int fd[2]);
int			is_exec_command(char **str);
int			is_other_command(char *str);
// REPLACING
char		*replace(char *str, int i, t_env *env);
char		*quote_replace(char *str, int i, t_env *env);
//char		**insert_files(char **command, int index);
int			ft_strchrpos(char *str, int searchedChar);
// REPLACING V2
void		env_bundle_init(t_var_env_bundle *var);
void		check_env(char **temp, t_env *env, int size);
int			srch_dollar(char c);
int			is_end_var(char c);
int			env_size(char *str, int i, t_env *env);
int	var_size(char *str, int i);
char		*ft_strrmchar(char *str, int pos);
char		*handle_env_quotes(char *str, int i, t_var_env_bundle *var);
// WILDCARD
int			srchr_wildcard(char *str);
char		*handle_wildcard(char *str, t_var_env_bundle *var);
char		*insert_files(char *pattern, char *str);
int			pattern_matching(char *pattern, char *filename);
int			count_wildcard(char *str, int i);
// INPUT REDIRECTION
int			find_i_red(t_io_red *redirection);
void		get_heredoc(int *p_fd, char *end);
// OUTPUT REDIRECTION
void		write_output(int buff_fd, t_io_red *redirection);
void		copy(int buff_fd, int *o_fd, int size);
void		copy_single(int buff_fd, int o_fd);
int			count_output_redirections(t_io_red *redirection);
// EXECUTION
int			execute(t_commands *temp, int buffer, int p_fd[2], t_env *env);
int			executefile(char **args, int i_fd, int o_fd, t_env *env);
int			executefullfile(char *cmd, char **args, int i_fd, int o_fd);
int			executecommand(char **args, int i_fd, int o_fd, t_env *env);
int			executebuiltin(char **cmd, int i_fd, int o_fd, t_env *envi);
int			commandbuiltin(char **arg, int i_fd, int o_fd, t_env *env);
char		*get_path(char *cmd, t_env *env);
// PIPES/EXEC UTILS
void		free_and_close(int *fd, int size);
void		free_cmd(t_commands **a);
void		free_red(t_io_red **a);
char		**get_filenames(void);
int			count_files(void);
// UTILITIES
void		free_split(char **split);
int			array_size(char **arr);
void		print_commands(t_commands *commands);
void		print_redirection(t_io_red *redirection);
void		init_pipes(int p_fd[2], int b_fd[2]);
char		*ft_getenv(t_env *env, char *name);
void		print_env(t_env *env);
// BUILTIN
int			pwd(void);
int			cd(char **args, t_env **env);
int			echo(char **args);
int			env(t_env **env, char **cmd);
int			unset(char **args, t_env **env);
int			export(char **args, t_env **env);
void		ft_exit(t_env *env, char **arg);
// BUILTIN UTILITIES
void		echo_check(char ***args);
int			arg_var_has_valid_chars(char *arg);
int	arg_val_has_valid_chars(char *arg);
int	desert_string(char ***array, int *size, const char *str, int position);
int	there_is_space(char *arg);
int			print_export(t_env **env);
int			ft_size_env(char **env);
int			ft_list_size(t_env *begin_list);
void		ft_env_push_back(t_env **begin_list, char *data);
void		sort_env_alphabetically(char **array);
void		free_array(char **array, int index);
char		**copy_environ(t_env **env);
int			print_export(t_env **env);
int			index_existing_var(char *arg, t_env **env);
int			equal_pos(char *str);
int			update(char *arg, int index, t_env **env);
t_env		*ft_create_var(char *arg);
int			add_var(char *arg, t_env **env);
int			export(char **args, t_env **env);
void		swap_strings(char **str1, char **str2);
// EXIT STATUS
void		add_exit_status(int exit_status, t_env **env);
void		*str_to_ptr(char *str);
char		*ptr_to_str(void *ptr);
void		add_red_to_env(t_io_red **red, t_env **env);
void		add_cmd_to_env(t_commands **commands, t_env **env);
int			print_file_error(char *args);
char		*ft_getallenv(t_env *env, char *name);
char	*clean_env(char *str);
#endif
