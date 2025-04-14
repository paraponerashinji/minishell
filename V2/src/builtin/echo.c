/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:23:14 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:54:48 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo_space(char *arg)
{
	char	**array;
	char	*temp;

	temp = ft_strjoin("echo ", arg);
	free(arg);
	array = ft_split(temp, ' ');
	/*int	i;
	i = 0;
	while (array[i])
	{
		printf("array[i]: %s\n", array[i]);
		i++;
	}*/
	echo(array);
	free(array);
}

int	there_is_space(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	print_echo(char **args, int i)
{
	while (args[i])
	{
		//printf("here? args[i]: %s\n", args[i]);
		/*
		if (there_is_space(args[i]))
		{
			//puts("hereeeo");
			echo_space(args[i]);
			i++;
			continue ;
		}
		*/
		//ft_putnbr_fd(i, 1);
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	jsh_echo_intermed(char **args, int index)
{
	int	i;
	int	j;

	i = index;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] && args[i][j] == 'n')
		{
			j++;
		}
		if (args[i][j] == '\0')
			i++;
		else
			break ;
		/*
		ft_putstr_fd("i: ", 1);
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
		ft_putnbr_fd(j, 1);
                ft_putchar_fd('\n', 1);
		*/
	}
	return (i);
}

int	echo(char **args)
{
	int	i;
	int	newline;
	int	j;
	//static int	check;

	i = 1;
	newline = 0;
	//puts("a");
	echo_check(&args);
	//ft_putstr_fd(args[0], 1);
	//ft_putchar_fd('\n', 1);
	//ft_putstr_fd(args[1], 1);
	//ft_putchar_fd('\n', 1);
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		//puts("ici?");
		j = 1;
		while (args[1][j] && args[1][j] == 'n')
		{
			j++;
		}
		if (args[1][j] == '\0')
		{
			newline++;
			i++;
		}
	}
	i = jsh_echo_intermed(args, i);
	print_echo(args, i);
	//if (newline >= 1 && args[i + 1])
	//	printf(" ");
	//printf("newline: %d\n", newline);
	if (newline == 0)
		printf("\n");
	return (0);
}