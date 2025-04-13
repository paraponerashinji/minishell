/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:17:41 by aharder           #+#    #+#             */
/*   Updated: 2025/04/13 19:05:07 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	check_env(t_commands *temp, t_env *env)
{
	int		i;
	int		k;
	char	*buffer;

	i = 0;
	while (temp->command[i] != NULL)
	{
		k = ft_strchrpos(temp->command[i], '$');
		if (temp->command[i][0] == '"' && k)
			temp->command[i] = quote_replace(temp->command[i], k, env);
		else if (temp->command[i][0] == '$')
			temp->command[i] = replace(temp->command[i], k, env);
		else if (temp->command[i][0] == '*' && temp->command[i][1] == '\0')
			temp->command = insert_files(temp->command, i);
		if (temp->command[i][0] == '"' || temp->command[i][0] == '\'')
		{
			buffer = temp->command[i];
			if (temp->command[i][0] != '\'')
				temp->command[i] = ft_strtrim(buffer, "\"");
			else if (temp->command[i][0] != '"')
				temp->command[i] = ft_strtrim(buffer, "'");
			free(buffer);
		}
		i++;
	}
}*/

void	env_bundle_init(t_var_env_bundle *var)
{
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->d_quotes = 0;
	var->s_quotes = 0;
}

void	check_env(char **temp, t_env *env, int size)
{
	t_var_env_bundle	var;

	env_bundle_init(&var);
	while (var.i < size)
	{
		var.j = 0;
		while (temp[var.i][var.j] != '\0')
		{
			var.k = srch_dollar(temp[var.i][var.j]);
			while ((var.k == 0 || var.s_quotes) && temp[var.i][var.j] != '\0')
			{
				//printf("j = %d\n", var.j);
				temp[var.i] = handle_env_quotes(temp[var.i], var.j, &var);
				if (!var.s_quotes && !var.d_quotes && var.j >= 0 && srchr_wildcard(&temp[var.i][var.j]))
					temp[var.i] = handle_wildcard(temp[var.i], &var);
				var.k = srch_dollar(temp[var.i][++var.j]);
			}
			var.k = env_size(temp[var.i], var.j, env);
			if (temp[var.i][var.j] != '\0')
				temp[var.i] = replace(temp[var.i], var.j, env);
			var.j += var.k;
			if (var.j > ft_strlen(temp[var.i]))
				break ;
		}
		var.i++;
	}
}

int	srch_dollar(char c)
{
	if (c == '$')
		return (1);
	else
		return (0);
}

int	is_end_var(char c)
{
	if (ft_isalnum(c))
		return (0);
	else if (c == '_')
		return (0);
	else
		return (1);
}

int	env_size(char *s, int i, t_env *env)
{
	char	*var;
	char	*value;
	int		size;

	if (s[i] != '\0' && is_end_var(s[i + 1]))
		return (1);
	var = ft_substr(s, i + 1, var_size(s, i + 1));
	value = ft_getenv(env, var);
	free(var);
	if (!value)
		return (0);
	size = ft_strlen(value);
	return (size);
}

int	var_size(char *str, int i)
{
	int	size;

	size = 0;
	if (i > ft_strlen(str))
		return (size);
	if (str[i] == '?')
		return (1);
	while (str[i] != '\0')
	{
		if (is_end_var(str[i]))
			break ;
		size++;
		i++;
	}
	return (size);
}

char	*ft_strrmchar(char *str, int pos)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	output = malloc((ft_strlen(str)) * sizeof(char));
	while (str[i] != '\0')
	{
		if (i != pos)
			output[j++] = str[i];
		i++;
	}
	output[j] = '\0';
	free(str);
	return (output);
}

char	*handle_env_quotes(char *str, int i, t_var_env_bundle *var)
{
	if (!var->s_quotes && str[i] == '"')
	{
		var->d_quotes = !var->d_quotes;
		str = ft_strrmchar(str, i);
		if (var->j >= 0)
			var->j--;
	}
	else if (!var->d_quotes && str[i] == '\'')
	{
		var->s_quotes = !var->s_quotes;
		str = ft_strrmchar(str, i);
		if (var->j >= 0)
			var->j--;
	}
	return (str);
}

int	var_size2(char *str, int i)
{
	if (str[i] == ' ')
		return (1);
	else if (str[i] == '\0')
		return (1);
	else
		return (0);
}

char	*replace(char *s, int i, t_env *env)
{
	char	*prefix;
	char	*suffix;
	char	*var;
	char	*value;

	prefix = ft_substr(s, 0, i);
	var = ft_substr(s, i + 1, var_size(s, i + 1));
	suffix = ft_substr(s, i + 1 + var_size(s, i + 1), ft_strlen(s) - i + 1 + var_size(s, i + 1));
	if (var_size2(s, i + 1) == 1)
		value = ft_strdup("$");
	else if (var == NULL || var[0] == '\0')
		value = ft_strdup(" ");
	else
		value = clean_env(ft_getenv(env, var));
	free(var);
	if (!value)
	{
		free(s);
		s = ft_strjoin(prefix, suffix);
		free(prefix);
		free(suffix);
		return (s);
	}
	free(s);
	s = ft_strjoin(prefix, value);
	free(prefix);
	prefix = ft_strjoin(s, suffix);
	free(s);
	free(suffix);
	free(value);
	return (prefix);
}

char	*quote_replace(char *str, int i, t_env *env)
{
	char	*buffer;
	char	*buff2;
	char	*buff3;
	int		j;

	j = i;
	while (str[j] != ' ' && str[j] != '"' && str[j] != '\0')
		j++;
	j = j - i;
	buffer = ft_substr(str, i, j);
	buff3 = ft_getenv(env, &buffer[1]);
	if (!buff3)
	{
		buff2 = str;
		str = ft_replacesubstr(buff2, buffer, "");
		free(buffer);
		free(buff2);
		return (str);
	}
	buff2 = str;
	str = ft_replacesubstr(buff2, buffer, buff3);
	free(buff2);
	free(buffer);
	return (str);
}
/*
char	*replace(char *str, int i, t_env *env)
{
	char	*buffer;
	char	*buff2;
	int		j;

	j = i;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	j = j - i;
	buffer = ft_substr(str, i, j);
	buff2 = str;
	str = ft_getenv(env, &buffer[1]);
	if (!str)
	{
		free(buffer);
		free(buff2);
		buffer = malloc(1 * sizeof(char));
		buffer[0] = '\0';
		return (buffer);
	}
	str = ft_replacesubstr(buff2, buffer, str);
	free(buff2);
	free(buffer);
	return (str);
}*/
/*
char	**insert_files(char **cmd, int index)
{
	char	**fn;
	char	**output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fn = get_filenames();
	output = malloc((array_size(fn) + array_size(cmd) + 1) * sizeof(char *));
	while (i++ < index)
		output[i - 1] = ft_strdup(cmd[i - 1]);
	while (fn[j] != NULL)
	{
		output[index + j] = ft_strdup(fn[j]);
		j++;
	}
	j = j + index;
	index++;
	while (cmd[index] != NULL)
		output[j++] = ft_strdup(cmd[index++]);
	output[j] = NULL;
	free_split(fn);
	free_split(cmd);
	return (output);
}*/

int	ft_strchrpos(char *str, int searchedChar)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == (char)searchedChar)
			return (i);
		str++;
		i++;
	}
	if (searchedChar == '\0')
		return (0);
	return (0);
}
