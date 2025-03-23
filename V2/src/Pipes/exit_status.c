/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:37:22 by aharder           #+#    #+#             */
/*   Updated: 2025/03/23 18:40:27 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_exit_status(int exit_status, t_env **env)
{
	int		index;
	char	*str;
	char	*num;

	num = ft_itoa(exit_status);
	str = ft_strjoin("?=", num);
	index = -1;
	index = index_existing_var(str, env);
	if (index >= 0)
		update(str, index, env);
	else
	{
		ft_env_push_back(env, str);
	}
	free(num);
	free(str);
}

char	*ptr_to_str(void *ptr)
{
	char			*hex;
	unsigned long	n;
	int				size;
	char			*mod;
	char			*result;

	hex = "0123456789abcdef";
	n = (unsigned long)ptr;
	size = sizeof(void *) * 2 + 3;
	mod = (char *)malloc(size);
	if (!mod)
		return (NULL);
	mod[--size] = '\0';
	while (n > 0)
	{
		mod[--size] = hex[n % 16];
		n = n / 16;
	}
	mod[--size] = 'x';
	mod[--size] = '0';
	result = strdup(mod + size);
	free(mod);
	return (result);
}

void	*str_to_ptr(char *str)
{
	unsigned long	n;
	int				i;

	n = 0;
	i = 0;
	if (str[0] == '0' && str[1] == 'x')
		i = 2;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			n = n * 16 + str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			n = n * 16 + str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			n = n * 16 + str[i] - 'A' + 10;
		else
			return (NULL);
		i++;
	}
	return ((void *)n);
}

void	add_red_to_env(t_io_red **red, t_env **env)
{
	int		index;
	char	*adress;
	char	*str;

	adress = ptr_to_str((void *)red);
	str = ft_strjoin("&=", adress);
	index = -1;
	index = index_existing_var(str, env);
	if (index >= 0)
		update(str, index, env);
	else
	{
		ft_env_push_back(env, str);
	}
	free(adress);
	free(str);
}

void	add_cmd_to_env(t_commands **commands, t_env **env)
{
	int		index;
	char	*adress;
	char	*str;

	adress = ptr_to_str((void *)commands);
	str = ft_strjoin("+=", adress);
	index = -1;
	index = index_existing_var(str, env);
	if (index >= 0)
		update(str, index, env);
	else
	{
		ft_env_push_back(env, str);
	}
	free(adress);
	free(str);
}
