/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:27:44 by aharder           #+#    #+#             */
/*   Updated: 2024/11/04 11:23:00 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	customstrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		j;
	size_t		dlen;
	int			slen;

	dlen = (size_t)ft_strlen(dest);
	slen = customstrlen(src);
	if (size <= dlen)
		return (size + slen);
	j = 0;
	while (src[j] != '\0' && dlen + j < size - 1)
	{
		dest[dlen + j] = src[j];
		j++;
	}
	dest[dlen + j] = '\0';
	return (dlen + slen);
}
