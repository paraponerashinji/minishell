/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:14:21 by aharder           #+#    #+#             */
/*   Updated: 2025/02/15 15:21:03 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	customstrlen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *dest, char *src)
{
	char	*joinedstring;
	int		i;
	int		j;
	int		lenstrs;

	i = 0;
	lenstrs = customstrlen2(dest) + customstrlen2(src);
	joinedstring = (char *)malloc(lenstrs * sizeof(char) + 1);
	if (joinedstring == NULL)
		return (NULL);
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
	return (joinedstring);
}
/*
char	*ft_strjoin(int size, char **strs)
{
	int		lenstrs;
	int		i;
	char	*joinedstring;

	i = 0;
	lenstrs = 0;
	while (i < size)
	{
		lenstrs = lenstrs + ft_strlen(strs[i]);
		i++;
	}
	lenstrs = lenstrs + (ft_strlen(sep) * (size)) + 1;
	joinedstring = malloc(lenstrs * sizeof(*joinedstring));
	i = 0;
	while (i <= size)
	{
		ft_strcat(joinedstring, strs[i]);
		if (i != size)
			ft_strcat(joinedstring, sep);
		i++;
	}
	return (joinedstring);
}*/
