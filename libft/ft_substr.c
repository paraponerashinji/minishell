/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:56:19 by aharder           #+#    #+#             */
/*   Updated: 2024/10/30 13:04:16 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	customstrlen3(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(const char *str, unsigned int start, size_t length)
{
	unsigned int	i;
	unsigned int	y;
	unsigned int	strlength;
	char			*dest;

	y = 0;
	strlength = customstrlen3(str);
	if (!str || start >= strlength)
	{
		dest = malloc(1 * sizeof(char));
		dest[y] = '\0';
		return (dest);
	}
	if (length > strlength - start)
		length = strlength - start;
	dest = malloc((length + 1) * sizeof(char));
	i = start;
	while (str[i] != '\0' && y < length)
	{
		dest[y] = str[i];
		i++;
		y++;
	}
	dest[y] = '\0';
	return (dest);
}
