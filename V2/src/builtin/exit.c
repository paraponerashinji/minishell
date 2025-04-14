/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:57 by aharder           #+#    #+#             */
/*   Updated: 2025/04/14 12:55:32 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_long(char *str)
{
	unsigned long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		printf("%lld %lld %lld\n", LLONG_MAX, (unsigned long long)LLONG_MIN, result);
		//if (result > LONG_MAX || (result * sign) < (long long unsigned)LONG_MIN)
		if (result > (unsigned long long)LLONG_MAX)
		{
			return (0);
		}
		if ((result > -(unsigned long long)LLONG_MIN) && (sign < 0))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi_long(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		if (result > LONG_MAX || (result * sign) < LONG_MIN)
			break ;
		i++;
	}
	return (result * sign);
}

int	check_arg_is_numeric(char *arg)
{
	int	i;

	if (!arg || arg[0] == '\0')
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_env *env, char **arg)
{
	void		*red;
	void		*commands;
	long long	exit_code;
	
	if (arg[1] != NULL && check_arg_is_numeric (arg[1]) && arg[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);	
		return ;
	}
	exit_code = 0;
	if (arg[1] && check_arg_is_numeric(arg[1]) == 1 && check_if_long(arg[1]) == 1)
	{
		exit_code = ft_atoi_long(arg[1]);
		if (exit_code >= 0)
			exit_code = exit_code % 256;
		else
			exit_code = exit_code % 256 + 256;
	}
	if (arg[1] && (check_arg_is_numeric(arg[1]) == 0 || check_if_long(arg[1]) == 0))
	{
		ft_putstr_fd("error: exit: numeric argument required\n", 2);
		exit_code = 2;
	}
	red = str_to_ptr(ft_getallenv(env, "&"));
	commands = str_to_ptr(ft_getallenv(env, "+"));
	free_red(red);
	free_cmd(commands);
	free_env(env);
	ft_putstr_fd("exit", 1);
	exit(exit_code);
}