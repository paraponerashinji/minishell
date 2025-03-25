/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:06:06 by aharder           #+#    #+#             */
/*   Updated: 2025/03/25 18:02:47 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
void	write_output(int buff_fd, t_io_red *redirection)
{
	t_io_red	*temp;
	int			*output_fd;
	int			i;

	i = count_output_redirections(redirection);
	temp = redirection;
	if (i == 0)
	{
		copy_single(buff_fd, 1);
		return ;
	}
	output_fd = malloc((i + 1) * sizeof(int));
	i = 0;
	while (temp != NULL)
	{
		if (temp->in_or_out == 7)
			output_fd[i++] = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->in_or_out == 6)
			output_fd[i++] = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		temp = temp->next;
	}
	copy(buff_fd, output_fd, i);
	free_and_close(output_fd, i);
	close(buff_fd);
}*/

void	write_output(int buff_fd, t_io_red *redirection)
{
	t_io_red	*temp;
	int			output_fd;

	output_fd = 1;
	temp = redirection;
	while (temp != NULL)
	{
		if (temp->in_or_out == 7)
		{
			if (output_fd != 1)
				close(output_fd);
			output_fd = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (temp->in_or_out == 6)
		{
			if (output_fd != 1)
				close(output_fd);
			output_fd = open(temp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		temp = temp->next;
	}
	copy_single(buff_fd, output_fd);
	if (output_fd != 1)
		close(output_fd);
	close(buff_fd);
}

void	copy(int buff_fd, int *o_fd, int size)
{
	char	*line;
	int		i;

	line = get_next_line(buff_fd);
	if (line == NULL)
		printf("erreur gnl");
	while (line != NULL)
	{
		i = 0;
		while (size > i)
		{
			write(o_fd[i++], line, ft_strlen(line));
		}
		free(line);
		line = get_next_line(buff_fd);
	}
}

void	copy_single(int buff_fd, int o_fd)
{
	char	*line;

	line = get_next_line(buff_fd);
	while (line != NULL)
	{
		write(o_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(buff_fd);
	}
}

int	count_output_redirections(t_io_red *redirection)
{
	int	count;

	count = 0;
	while (redirection != NULL)
	{
		if (redirection->in_or_out == 7 || redirection->in_or_out == 6)
			count++;
		redirection = redirection->next;
	}
	return (count);
}
