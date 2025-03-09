/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bordel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:24:03 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 01:10:13 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quotes_bis(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] != quote && s[i] != '\0')
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

int	handle_operator(char *s, int *i, int *j, int *output)
{
	output[(*j)++] = find_op(&s[(*i)++]);
	if (output[*j - 1] == 1 || output[*j - 1] == 3)
		(*i)++;
	else if (output[*j - 1] == 4 || output[*j - 1] == 6)
		(*i)++;
	return (1);
}

void	init_list(char *list)
{
	list[0] = '|';
	list[1] = '<';
	list[2] = '>';
	list[3] = '&';
	list[4] = '\0';
}

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
