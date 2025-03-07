/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:08:07 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 02:29:56 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_heredoc(int *p_fd, char *end)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if (ft_strcmp(heredoc, end) == 0)
		{
			free(heredoc);
			break ;
		}
		write(p_fd[1], heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
}

int	find_i_red(t_io_red *redirection)
{
	t_io_red	*temp;
	int			input_fd[2];

	temp = redirection;
	input_fd[0] = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		if (temp->in_or_out == 5)
		{
			input_fd[0] = open(temp->file, O_RDONLY);
		}
		if (temp->in_or_out == 4)
		{
			if (input_fd[0])
				close(input_fd[0]);
			pipe(input_fd);
			get_heredoc(input_fd, temp->file);
			close(input_fd[1]);
		}
		temp = temp->next;
	}
	return (input_fd[0]);
}
