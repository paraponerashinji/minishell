/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:09:42 by aharder           #+#    #+#             */
/*   Updated: 2025/03/23 15:40:27 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmp(char c)
{
	int		i;
	char	list[5];

	init_list(list);
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
	int		i[2];
	int		in_segment;

	i[0] = 0;
	i[1] = 0;
	in_segment = 0;
	while (s[i[0]] != '\0')
	{
		if ((s[i[0]] == '"' || s[i[0]] == '\'') && !in_segment)
		{
			i[0] = handle_quotes_bis(s, i[0]);
			i[1]++;
		}
		if (s[i[0]] != c && !in_segment)
		{
			in_segment = 1;
			i[1]++;
		}
		if (s[i[0]] == c || s[i[0]] == '"' || s[i[0]] == '\'')
			in_segment = 0;
		if (s[i[0]] != '\0')
			i[0]++;
	}
	return (i[1]);
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
