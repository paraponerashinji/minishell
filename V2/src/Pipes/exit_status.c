/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:37:22 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 16:25:33 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_exit_status(int exit_status, t_env **env)
{
	int		i;
	int		index;
	char	*str;
	char	*num;

	num = ft_itoa(exit_status);
	str = ft_strjoin("?=", num);
	index = -1;
	i = 1;
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

void	ptr_to_str(void *ptr, char *mod, int size)
{
	char	*hex;
	int		i;
	unsigned long	n;

	n = (unsigned long)ptr;
	hex = "0123456789abcdef";
	i = size;
	mod[i--] = '\0';
	while (n > 0)
	{
		mod[i--] = hex[n % 16];
		n = n / 16;
	}
	mod[i--] = 'x';
	mod[i--] = '0';
}
void	add_red_to_env(t_io_red **red, t_env **env)
{
	int		i;
	int		index;
	char	adress[20];
	char	*str;

	ptr_to_str((void *)red, adress, sizeof(adress));
	str = ft_strjoin("&=", adress);
	index = -1;
	i = 1;
	index = index_existing_var(str, env);
	if (index >= 0)
		update(str, index, env);
	else
	{
		ft_env_push_back(env, str);
	}
}