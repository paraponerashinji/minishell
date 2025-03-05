/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreprinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:23:56 by aharder           #+#    #+#             */
/*   Updated: 2024/11/05 15:25:54 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsignednbr(unsigned int n)
{
	if (n == 0)
	{
		return (ft_putchar('0'));
	}
	if (n > 9)
	{
		ft_putunsignednbr(n / 10);
	}
	ft_putchar(n % 10 + '0');
	return (findlength(n));
}

int	ft_putptr(unsigned long n)
{
	char	*hex;
	char	mod[17];
	int		i;

	hex = "0123456789abcdef";
	if (n == 0)
		return (ft_putstr("(nil)"));
	i = 16;
	mod[i--] = '\0';
	while (n > 0)
	{
		mod[i--] = hex[n % 16];
		n = n / 16;
	}
	ft_putstr("0x");
	i = 2 + ft_putstr(&mod[i + 1]);
	return (i);
}
