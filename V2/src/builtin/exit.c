/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:57 by aharder           #+#    #+#             */
/*   Updated: 2025/03/12 00:57:17 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_env *env)
{
	void	*red;
	void	*commands;

	red = str_to_ptr(ft_getenv(env, "&"));
	commands = str_to_ptr(ft_getenv(env, "+"));
	free_red(red);
	free_cmd(commands);
	free_env(env);
	exit(0);
}
