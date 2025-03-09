/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:20:52 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 21:45:45 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commandbuiltin(char **arg, t_env *env)
{
	int	exit_status;

	(void)env;
	exit_status = 0;
	if (strcmp(arg[0], "cd") == 0)
	{
		exit_status = cd(arg);
	}
	return (exit_status);
}