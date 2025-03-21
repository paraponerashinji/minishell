/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_utilities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:23 by aharder           #+#    #+#             */
/*   Updated: 2025/03/21 10:35:45 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	assign_start_value(t_var_bundle *var)
{
	var->i = 0;
	var->j = 0;
	var->y = 0;
	var->s_quotes = 0;
	var->d_quotes = 0;
}

char	**perror_and_free(char **output, int size)
{
	int	i;

	i = 0;
	printf("Error: unmatched quotes\n");
	while (i < size)
	{
		free(output[i]);
		i++;
	}
	free(output);
	return (NULL);
}

char	*crop_str(char *s, int start, int end)
{
	char	*output;

	output = malloc((end - start + 1) * sizeof(char));
	ft_strncpy(output, s + start, (end - start));
	output[end - start] = '\0';
	return (output);
}
