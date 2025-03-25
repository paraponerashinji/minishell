/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:18:05 by aharder           #+#    #+#             */
/*   Updated: 2025/03/25 18:04:41 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_segment_end(char *s, char c, int i)
{
	char	quote;

	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] != quote && s[i] != '\0')
				i++;
			if (s[i] != quote)
			{
				printf("Error: bracket\n");
				return (-1);
			}
		}
		i++;
	}
	return (i);
}

char	*write_segment(char *s, int start, int end)
{
	char	*output;
	int		i;

	output = malloc((end - start + 1) * sizeof(char));
	i = 0;
	while (start < end)
		output[i++] = s[start++];
	output[i] = '\0';
	return (output);
}

char	**second_split(char *s, char c)
{
	int		i[3];
	char	**output;

	i[0] = 0;
	i[1] = 0;
	if (!s)
		return (NULL);
	output = malloc((splitlen(s, ' ') + 1000) * sizeof(char *));
	if (!output)
		return (NULL);
	while (s[i[0]] != '\0')
	{
		while (s[i[0]] == c)
			i[0]++;
		if (s[i[0]] == '\0')
			break ;
		i[2] = find_segment_end(s, c, i[0]);
		output[i[1]] = write_segment(s, i[0], i[2]);
		if (!output[i[1]])
			return (NULL);
		i[0] = i[2];
		i[1]++;
	}
	output[i[1]] = NULL;
	return (output);
}
