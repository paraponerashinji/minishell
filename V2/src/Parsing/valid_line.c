/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:57:27 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 01:08:31 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_pipe_error(void)
{
	printf("minishell: syntax error\n");
	return (1);
}

int	valid_line(t_commands *cmd, t_io_red *red)
{
	t_commands	*buff;

	(void)red;
	buff = cmd;
	while (buff != NULL)
	{
		if (buff->command[0] == NULL)
			return (print_pipe_error());
		if (buff->command[0][0] == '\0')
			return (print_pipe_error());
		buff = buff->next;
	}
	return (0);
}
