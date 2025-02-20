/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:26:43 by aharder           #+#    #+#             */
/*   Updated: 2024/10/31 11:05:25 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	splitlen2(const char *s, char c)
{
	int	i;
	int	split;

	i = 0;
	split = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			split++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (split);
}

int	splitsize(const char *s, char c, int start)
{
	int	i;
	int	y;

	i = start;
	y = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		y++;
		i++;
	}
	return (y);
}

t_var_bordel	defining_start_value(t_var_bordel var)
{
	var.y = 0;
	var.i = 0;
	var.len = 0;
	var.split = 0;
	return (var);
}

char	**ft_split(const char *s, char c)
{
	t_var_bordel	var;
	char			**output;

	var.i = 0;
	var = defining_start_value(var);
	if (!s)
		return (NULL);
	output = (char **)malloc((splitlen2(s, c) + 1) * sizeof(char *));
	while (var.split < splitlen2(s, c))
	{
		while (s[var.i] == c)
			var.i++;
		var.len = splitsize(s, c, var.i);
		output[var.split] = malloc((var.len + 1) * sizeof(char));
		var.y = 0;
		while (var.y < var.len)
		{
			output[var.split][var.y++] = s[var.i++];
		}
		output[var.split][var.y] = '\0';
		var.split++;
	}
	output[var.split] = NULL;
	return (output);
}
