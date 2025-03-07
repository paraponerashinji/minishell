/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:59:16 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 16:17:05 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(t_env *env, char *name)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (strcmp(env->value, name) == 0)
			return (env->result);
		temp = temp->next;
	}
	return (NULL);
}
