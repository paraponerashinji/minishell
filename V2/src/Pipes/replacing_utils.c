/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:59:16 by aharder           #+#    #+#             */
/*   Updated: 2025/03/12 01:18:36 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(t_env *env, char *name)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (strcmp(temp->value, name) == 0)
			return (temp->result);
		temp = temp->next;
	}
	return (NULL);
}

int	print_file_error(char *args)
{
	int	status;

	printf("%s: file not found\n", args);
	status = 127;
	return (status);
}
