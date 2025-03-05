/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:17:10 by aharder           #+#    #+#             */
/*   Updated: 2024/11/06 16:26:51 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		y;
	va_list	args;

	i = 0;
	y = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			y = y + gettype(str[i++], args);
		}
		else
		{
			ft_putchar(str[i++]);
			y++;
		}
	}
	va_end(args);
	return (y);
}

int	gettype(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr((unsigned long)va_arg(args, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsignednbr(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_puthexlower(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_puthexupper(va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_putchar('%'));
	{
		ft_putchar('%');
		ft_putchar(c);
	}
	return (2);
}
