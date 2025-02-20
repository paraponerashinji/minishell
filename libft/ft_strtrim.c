/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:00:06 by aharder           #+#    #+#             */
/*   Updated: 2024/10/31 11:42:44 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	anothercustomstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	issetchar(char c, const char *set)
{
	int	i;
	int	setlen;

	i = 0;
	setlen = anothercustomstrlen(set);
	while (i < setlen)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	customstrlen(const char *str, const char *set)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	while (str[i] && issetchar(str[i], set))
		i++;
	y = anothercustomstrlen(str) - 1;
	while (y >= i && issetchar(str[y], set))
		y--;
	count = y - i + 1;
	if (count < 1)
		return (0);
	return (count);
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*output;
	int		i;
	int		decalage;

	i = 0;
	if (!str || !set)
		return (NULL);
	output = malloc((customstrlen(str, set) + 1) * sizeof(char));
	if (!output)
		return (NULL);
	decalage = 0;
	while (issetchar(str[decalage], set) == 1)
		decalage++;
	while (i < customstrlen(str, set))
	{
		output[i] = str[i + decalage];
		i++;
	}
	output[i] = '\0';
	return (output);
}
