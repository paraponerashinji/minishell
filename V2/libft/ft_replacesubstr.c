/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replacesubstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:51:18 by aharder           #+#    #+#             */
/*   Updated: 2025/02/24 15:45:39 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static char	*find(char *temp_result, char *to_replace, char *str, int *len)
{
	char	*buffer;

	buffer = (char *)ft_strnstr(temp_result, to_replace, ft_strlen(str));
	*len = buffer - temp_result;
	return (buffer);
}

static void	insert(char **t_result, char **t_insert, char *replacement, int len)
{
	ft_strncpy(*t_insert, *t_result, len);
	*t_insert += len;
	ft_strncpy(*t_insert, replacement, ft_strlen(replacement));
	*t_insert += ft_strlen(replacement);
	*t_result += len;
}

char	*ft_replacesubstr(char	*str, char *to_replace, char *replacement)
{
	int		i[4];
	char	*string[4];

	i[1] = 0;
	string[0] = str;
	string[0] = (char *)ft_strnstr(string[0], to_replace, ft_strlen(string[0]));
	while (string[0])
	{
		i[1]++;
		string[0] += ft_strlen(to_replace);
		string[0] = (char *)ft_strnstr(string[0], to_replace, ft_strlen(str));
	}
	string[3] = malloc((ft_strlen(str) - ft_strlen
				(to_replace) * i[1] + ft_strlen
				(replacement) * i[1] + 1) * sizeof(char));
	string[1] = str;
	string[2] = string[3];
	while (i[1]--)
	{
		string[0] = find(string[1], to_replace, str, &i[0]);
		insert(&string[1], &string[2], replacement, i[0]);
		string[1] += ft_strlen(to_replace);
	}
	ft_strcpy(string[2], string[1]);
	return (string[3]);
}
