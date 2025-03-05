/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:34:28 by aharder           #+#    #+#             */
/*   Updated: 2024/11/04 11:28:46 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strnstr(const char *str, const char *searchedStr, size_t n)
{
	size_t		i;
	int			j;
	int			ibuffer;

	i = 0;
	if (searchedStr[i] == '\0')
		return (str);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		if (searchedStr[j] == str[i])
		{
			ibuffer = i;
			while (searchedStr[j] == str[i] && str[i] != '\0' && i < n)
			{
				j++;
				i++;
			}
			if (searchedStr[j] == '\0')
				return (&str[ibuffer]);
			i = ibuffer;
		}
		i++;
	}
	return (0);
}
