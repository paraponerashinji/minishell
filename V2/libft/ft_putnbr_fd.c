/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:35:54 by aharder           #+#    #+#             */
/*   Updated: 2024/10/30 10:24:09 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"
/*
void	ft_putnbr_fd(int n, int fd)
{
	char	output[11];
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		i++;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return;
	}
	while (n != 0)
	{
		output[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	while (i > 0)
	{
		ft_putchar_fd(output[i - 1], fd);
		i--;
	}
}
*/
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd((n % 10 + '0'), fd);
}
