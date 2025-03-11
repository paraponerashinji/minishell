/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:47:27 by aharder           #+#    #+#             */
/*   Updated: 2025/03/11 14:40:13 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_and_close(int *fd, int size)
{
	int	i;

	i = 0;
	while (size > i)
		close(fd[i++]);
	free(fd);
}

void	free_cmd(t_commands **a)
{
	t_commands	*tmp;
	int			i;

	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		i = 0;
		while (tmp->command[i] != NULL)
			free(tmp->command[i++]);
		free(tmp->command);
		free(tmp);
	}
}

void	free_red(t_io_red **a)
{
	t_io_red	*tmp;

	while (*a)
	{
		tmp = *a;
		*a = (*a)->next;
		free(tmp->file);
		free(tmp);
	}
}

char	**get_filenames(void)
{
	struct dirent	*entry;
	DIR				*dp;
	char			**filenames;
	int				count;
	int				i;

	i = 0;
	count = count_files();
	filenames = malloc((count + 1) * sizeof(char *));
	dp = opendir(".");
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			filenames[i++] = ft_strdup(entry->d_name);
		entry = readdir(dp);
	}
	filenames[i] = NULL;
	closedir(dp);
	return (filenames);
}

int	count_files(void)
{
	struct dirent	*entry;
	DIR				*dp;
	int				count;

	count = 0;
	dp = opendir(".");
	if (dp == NULL)
		return (0);
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			count++;
		entry = readdir(dp);
	}
	closedir(dp);
	return (count);
}
