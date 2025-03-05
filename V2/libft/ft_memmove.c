/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:21:46 by aharder           #+#    #+#             */
/*   Updated: 2024/10/29 14:48:50 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dest, const void *src, int size)
{
	unsigned char	*dest2;
	unsigned char	*src2;
	int				i;

	i = 0;
	dest2 = (unsigned char *) dest;
	src2 = (unsigned char *) src;
	if (dest2 < src2)
	{
		while (i < size)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	else
	{
		i = size;
		while (i > 0)
		{
			dest2[i - 1] = src2[i - 1];
			i--;
		}
	}
	return (dest);
}
