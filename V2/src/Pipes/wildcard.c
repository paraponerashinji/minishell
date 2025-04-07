/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:42:58 by aharder           #+#    #+#             */
/*   Updated: 2025/04/08 00:28:19 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	srchr_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		if (str[i] == '*')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}
char	*handle_wildcard(char *str, int i)
{
	char	*output;
	char	*pattern;
	int		j;
	int		k;

	j = i;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	pattern = malloc((j - i + 1) * sizeof(char));
	k = i;
	while (k < j)
	{
		pattern[k - i] = str[k];
		k++;
	}
	pattern[k - i] = '\0';
	output = insert_files(pattern, str);
	free(str);
	free(pattern);
	return (output);
}

int	count_wildcard(char *str, int i)
{
	char	*output;
	char	*pattern;
	int		j;
	int		k;

	j = i;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	pattern = malloc((j - i + 1) * sizeof(char));
	k = i;
	while (k < j)
	{
		pattern[k - i] = str[k];
		k++;
	}
	pattern[k - i] = '\0';
	output = insert_files(pattern, str);
	k = splitlen(output, ' ');
	free(output);
	free(pattern);
	return (k);
}

char	*insert_files(char *pattern, char *str)
{
	char	**filenames;
	char	*temp;
	int		k;

	filenames = get_filenames();
	k = 0;
	temp = NULL;
	
	while (filenames[k] != NULL)
	{
		if (pattern_matching(pattern, filenames[k]))
		{
			if (!temp)
			{
				temp = ft_strdup(filenames[k]);
			}
			else
			{
				temp = ft_strjoinfree(temp, " ");
				temp = ft_strjoinfree(temp, filenames[k]);
			}
		}
		k++;
	}
	str = ft_replacesubstr(str, pattern, temp);
	free(temp);
	free_split(filenames);
	return (str);
}
int	pattern_matching(char *pattern, char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *filename == '\0')
		return (0);
	if (*pattern == *filename)
		return (pattern_matching(pattern + 1, filename + 1));
	if (*pattern == '*')
	{
		return (pattern_matching(pattern + 1, filename) || pattern_matching(pattern, filename + 1));
	}
	return (0);
}