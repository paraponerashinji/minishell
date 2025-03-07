/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:17:41 by aharder           #+#    #+#             */
/*   Updated: 2025/03/07 02:37:13 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_env(t_commands *temp)
{
	int	i;
	int	k;

	i = 0;
	while (temp->command[i] != NULL)
	{
		k = ft_strchrpos(temp->command[i], '$');
		if (temp->command[i][0] == '"' && k)
			temp->command[i] = quote_replace(temp->command[i], k);
		else if (temp->command[i][0] == '$')
			temp->command[i] = replace(temp->command[i], k);
		else if (temp->command[i][0] == '*' && temp->command[i][1] == '\0')
			temp->command = insert_files(temp->command, i);
		i++;
	}
}

char	*quote_replace(char *str, int i)
{
	char	*buffer;
	char	*buff2;
	int		j;

	j = i;
	while (str[j] != ' ' && str[j] != '"' && str[j] != '\0')
		j++;
	j = j - i;
	buffer = ft_substr(str, i, j);
	str = getenv(&buffer[1]);
	buff2 = str;
	str = ft_replacesubstr(buff2, buffer, str);
	free(buff2);
	free(buffer);
	return (str);
}

char	*replace(char *str, int i)
{
	char	*buffer;
	char	*buff2;
	int		j;

	j = i;
	while (str[j] != ' ' && str[j] != '\0')
		j++;
	j = j - i;
	buffer = ft_substr(str, i, j);
	str = getenv(&buffer[1]);
	buff2 = str;
	str = ft_replacesubstr(buff2, buffer, str);
	free(buff2);
	free(buffer);
	return (str);
}

char	**insert_files(char **cmd, int index)
{
	char	**fn;
	char	**output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fn = get_filenames();
	output = malloc((array_size(fn) + array_size(cmd) + 1) * sizeof(char *));
	while (i++ < index)
		output[i - 1] = ft_strdup(cmd[i - 1]);
	while (fn[j] != NULL)
	{
		output[index + j] = ft_strdup(fn[j]);
		j++;
	}
	j = j + index;
	index++;
	while (cmd[index] != NULL)
		output[j++] = ft_strdup(cmd[index++]);
	output[j] = NULL;
	free_split(fn);
	free_split(cmd);
	return (output);
}

int	ft_strchrpos(char *str, int searchedChar)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == (char)searchedChar)
			return (i);
		str++;
		i++;
	}
	if (searchedChar == '\0')
		return (0);
	return (0);
}
