/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:25:45 by aharder           #+#    #+#             */
/*   Updated: 2025/03/09 18:58:37 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env(t_env **env)
{
	t_env		*ptr;

	ptr = *env;
	while (ptr)
	{
		printf("%s=%s\n", ptr->value, ptr->result);
		ptr = ptr->next;
	}
	return (0);
}