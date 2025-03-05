/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:15:57 by aharder           #+#    #+#             */
/*   Updated: 2024/11/12 12:00:51 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *source, int size)
{
	unsigned char	*dest2;
	unsigned char	*source2;
	int				i;

	i = 0;
	dest2 = (unsigned char *) dest;
	source2 = (unsigned char *) source;
	while (i < size)
	{
		dest2[i] = source2[i];
		i++;
	}
	return (dest);
}
