/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:08:36 by aharder           #+#    #+#             */
/*   Updated: 2024/11/07 11:02:55 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	size;

	if (str == NULL)
		return (ft_putstr("(null)"));
	size = ft_strlen(str);
	write(1, str, size);
	return (size);
}

int	ft_putnbr(int n)
{
	int	length;

	length = 0;
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	if (n == 0)
	{
		return (ft_putchar('0'));
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
		length++;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar(n % 10 + '0');
	return (findlength((unsigned int)n) + length);
}

int	ft_puthexupper(unsigned int n)
{
	char	*hex;
	char	mod[9];
	int		i;

	hex = "0123456789ABCDEF";
	i = 8;
	if (n == 0)
		return (ft_putstr("0"));
	mod[i--] = '\0';
	while (n > 0)
	{
		mod[i--] = hex[n % 16];
		n = n / 16;
	}
	return (ft_putstr(&mod[i + 1]));
}

int	ft_puthexlower(unsigned int n)
{
	char	*hex;
	char	mod[9];
	int		i;

	hex = "0123456789abcdef";
	i = 8;
	if (n == 0)
		return (ft_putstr("0"));
	mod[i--] = '\0';
	while (n > 0)
	{
		mod[i--] = hex[n % 16];
		n = n / 16;
	}
	return (ft_putstr(&mod[i + 1]));
}
