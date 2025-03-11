/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:37:22 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 13:44:38 by aharder          ###   ########.fr       */
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
