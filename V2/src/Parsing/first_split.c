/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:10:41 by aharder           #+#    #+#             */
/*   Updated: 2025/03/21 10:35:28 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**first_split(char *s)
{
	t_var_bundle	var;
	char			**output;
	int				split_size;

	assign_start_value(&var);
	split_size = first_split_size(s);
	output = malloc((split_size + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	process_string(s, &var, output);
	if (var.d_quotes || var.s_quotes)
		return (perror_and_free(output, split_size));
	output[var.y] = NULL;
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
		if (var->i > ft_strlen(s))
			break ;
	}
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

void	handle_quotes(t_var_bundle *var, char c)
{
	if (!var->s_quotes && c == '"')
		var->d_quotes = !var->d_quotes;
	else if (!var->d_quotes && c == '\'')
		var->s_quotes = !var->s_quotes;
}

int	srch_operator(char *s)
{
	if (s[0] == '&' && s[1] == '&')
		return (2);
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
		return (1 + (s[0] == s[1]));
	return (0);
}
