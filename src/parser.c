/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:00:20 by aharder           #+#    #+#             */
/*   Updated: 2025/02/26 02:20:35 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "../minishell.h"

typedef struct s_var_bundle
{
	int	i;
	int	j;
	int	y;
	int	s_quotes;
	int	d_quotes;
}	t_var_bundle;

void	assign_start_value(t_var_bundle *var)
{
	var->i = 0;
	var->j = 0;
	var->y = 0;
	var->s_quotes = 0;
	var->d_quotes = 0;
}

char **perror_and_free(char **output) {
    int i = 0;

    printf("Error: unmatched quotes");
    while (output[i] != NULL) {
        free(output[i]);
        i++;
    }
    free(output);
    return NULL;
}

void	handle_quotes(t_var_bundle *var, char c)
{
	if (!var->s_quotes && c == '"')
		var->d_quotes = !var->d_quotes;
	else if (!var->d_quotes && c == '\'')
		var->s_quotes = !var->s_quotes;
}

int	srch_operator(char *s)
{
	    if (s[0] == '|' || s[0] == '&' || s[0] == '<' || s[0] == '>')
		    return (1 + (s[0] == s[1]));
	    return (0);
}

int	first_split_size(char *s)
{
	int	count;
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	count = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (s[i] != '\0')
	{
		if (!s_quotes && s[i] == '"')
			d_quotes = !d_quotes;
		else if (!d_quotes && s[i] == '\'')
			s_quotes = !s_quotes;
		if (!s_quotes && !d_quotes && srch_operator(&s[i]))
		{
			count++;
			i += srch_operator(&s[i]);
		}
		else
			i++;
	}
	printf("%d\n", count);
	return (count + 1);
}

char	*crop_str(char *s, int start, int end)
{
	char	*output;

	output = malloc((end - start + 1) * sizeof(char));
	ft_strncpy(output, s + start, (end - start));
	output[end - start] = '\0';
	return (output);
}

void	process_string(char *s, t_var_bundle *var, char **output)
{
	int	i;

	while (s[var->i] != '\0')
	{
		i = srch_operator(&s[var->i]);
		var->j = var->i;
		while ((i == 0 || var->s_quotes || var->d_quotes) && s[var->j] != '\0')
		{
			handle_quotes(var, s[var->j]);
			var->j++;
			if (i == 0)
				i = srch_operator(&s[var->j]);
		}
		output[var->y] = crop_str(s, var->i, var->j);
		var->y++;
		var->i = var->j + i;
	}
}

char	**first_split(char *s)
{
	t_var_bundle	var;
	char	**output;
	int i;

	assign_start_value(&var);
	i = first_split_size(s);
	output = malloc((i + 1) * sizeof(char *));
	process_string(s, &var, output);
	if (var.d_quotes || var.s_quotes)
		return (perror_and_free(output));
	output[var.i] = NULL;
	return (output);
}*/

#include "../minishell.h"

typedef struct s_var_bundle
{
	int	i;
	int	j;
	int	y;
	int	s_quotes;
	int	d_quotes;
}	t_var_bundle;

void	assign_start_value(t_var_bundle *var)
{
	var->i = 0;
	var->j = 0;
	var->y = 0;
	var->s_quotes = 0;
	var->d_quotes = 0;
}

char	**perror_and_free(char **output)
{
	int i = 0;

	printf("Error: unmatched quotes");
	while (output[i] != NULL)
	{
		free(output[i]);
		i++;
	}
	free(output);
	return NULL;
}

void	handle_quotes(t_var_bundle *var, char c)
{
	if (!var->s_quotes && c == '"')
		var->d_quotes = !var->d_quotes;
	else if (!var->d_quotes && c == '\'')
		var->s_quotes = !var->s_quotes;
}

int	srch_operator(char *s)
{
	if (s[0] == '|' || s[0] == '&' || s[0] == '<' || s[0] == '>')
		return (1 + (s[0] == s[1]));
	return (0);
}

int	first_split_size(char *s)
{
	int	count;
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	count = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (s[i] != '\0')
	{
		if (!s_quotes && s[i] == '"')
			d_quotes = !d_quotes;
		else if (!d_quotes && s[i] == '\'')
			s_quotes = !s_quotes;
		if (!s_quotes && !d_quotes && srch_operator(&s[i]))
		{
			count++;
			i += srch_operator(&s[i]);
		}
		else
			i++;
	}
	return (count + 1);
}

char	*crop_str(char *s, int start, int end)
{
	char	*output;

	output = malloc((end - start + 1) * sizeof(char));
	ft_strncpy(output, s + start, (end - start));
	output[end - start] = '\0';
	return (output);
}

void	process_string(char *s, t_var_bundle *var, char **output)
{
	int	i;

	while (s[var->i] != '\0')
	{
		i = srch_operator(&s[var->i]);
		var->j = var->i;
		while ((i == 0 || var->s_quotes || var->d_quotes) && s[var->j] != '\0')
		{
			handle_quotes(var, s[var->j]);
			var->j++;
			if (i == 0)
				i = srch_operator(&s[var->j]);
		}
		output[var->y] = crop_str(s, var->i, var->j);
		var->y++;
		var->i = var->j + i;
	}
}

char	**first_split(char *s)
{
	t_var_bundle	var;
	char	**output;
	int		split_size;

	assign_start_value(&var);
	split_size = first_split_size(s);
	output = malloc((split_size + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	process_string(s, &var, output);
	if (var.d_quotes || var.s_quotes)
		return (perror_and_free(output));
	output[var.y] = NULL;
	return (output);
}
