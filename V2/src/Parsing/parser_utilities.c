/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:09:42 by aharder           #+#    #+#             */
/*   Updated: 2025/03/06 23:12:16 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char c)
{
	int	i;
	char	list[] = { '|', '<', '>', '&', '\0'};

	i = 0;
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
}

int	splitlen(char *s, char c)
{
	int		i;
	int		count;
	int		in_segment;
	char	quote;

	i = 0;
	count = 0;
	in_segment = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && !in_segment)
		{
			quote = s[i];
			i++;
			while (s[i] != quote && s[i] != '\0')
				i++;
			if (s[i] == quote)
				i++;
			in_segment = 1;
			count++;
		}
		else if (s[i] != c && !in_segment)
		{
			in_segment = 1;
			count++;
		}
		else if (s[i] == c)
			in_segment = 0;
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

int	find_op(char *s)
{
	if (s[0] == '|' && s[1] == '|')
		return (1);
	else if (s[0] == '|')
		return (2);
	else if (s[0] == '&' && s[1] == '&')
		return (3);
	else if (s[0] == '<' && s[1] == '<')
		return (4);
	else if (s[0] == '<')
		return (5);
	else if (s[0] == '>' && s[1] == '>')
		return (6);
	else if (s[0] == '>')
		return (7);
	else
		return (0);
}

int	array_size(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}