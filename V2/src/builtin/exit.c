/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:46:57 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 16:00:48 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_env *env, t_commands *commands, t_io_red *red)
{
	free_red(&red);
	free_cmd(&commands);
	free_env(&env);
	exit(0);
}
