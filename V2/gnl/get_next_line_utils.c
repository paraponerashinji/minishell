/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:10:21 by aharder           #+#    #+#             */
/*   Updated: 2024/11/14 11:12:27 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strchr2(char *str, int searchedChar)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == (char)searchedChar)
			return (str);
		str++;
	}
	if (searchedChar == '\0')
		return (str);
	return (0);
}

int	ft_strlen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin2(char *dest, const char *src)
{
	char	*joinedstring;
	int		i;
	int		j;

	i = 0;
	joinedstring = malloc(ft_strlen2(dest) + ft_strlen2(src) + 1);
	while (dest[i] != '\0')
	{
		joinedstring[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		joinedstring[i + j] = src[j];
		j++;
	}
	joinedstring[i + j] = '\0';
	free(dest);
	return (joinedstring);
}
