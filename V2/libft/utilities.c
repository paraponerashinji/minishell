/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:12:43 by aharder           #+#    #+#             */
/*   Updated: 2024/11/04 16:12:59 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getargcount(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	findlength(unsigned int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}
