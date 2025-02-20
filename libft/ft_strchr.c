/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:16:48 by aharder           #+#    #+#             */
/*   Updated: 2024/10/31 11:58:52 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int searchedChar)
{
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
