/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:40:21 by aharder           #+#    #+#             */
/*   Updated: 2024/11/04 11:11:19 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*table;

	if (elementSize != 0 && elementCount > (size_t)-1 / elementSize)
		return (NULL);
	table = malloc(elementCount * elementSize);
	if (table == NULL)
		return (table);
	ft_bzero(table, elementCount * elementSize);
	return (table);
}
