/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:00:10 by aharder           #+#    #+#             */
/*   Updated: 2025/02/16 14:09:08 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main()
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		printf("Error");
}
