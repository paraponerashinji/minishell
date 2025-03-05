/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:50:38 by aharder           #+#    #+#             */
/*   Updated: 2024/11/14 11:14:59 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*file[1024];
	char		*output;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	file[fd] = init_file(fd, file[fd]);
	if (!file[fd])
		return (NULL);
	output = pushingoutput(file[fd]);
	if (output[0] == '\0')
	{
		free(output);
		file[fd] = deletefile(file[fd]);
		return (NULL);
	}
	if (!output)
		return (NULL);
	file[fd] = deletefile(file[fd]);
	return (output);
}

char	*init_file(int fd, char *file)
{
	char	*buffer;
	int		length;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	length = 1;
	while (!ft_strchr2(file, '\n') && length > 0)
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if (length < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[length] = '\0';
		if (length == 0)
			break ;
		if (!file)
		{
			file = malloc(1 * sizeof(char));
			file[0] = '\0';
		}
		file = ft_strjoin2(file, buffer);
	}
	free(buffer);
	return (file);
}

char	*pushingoutput(char *file)
{
	char	*output;
	int		i;

	if (!file)
		return (NULL);
	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	output = malloc ((i + 2) * sizeof(char));
	if (!output)
		return (NULL);
	i = 0;
	while (file[i] != '\n' && file[i])
	{
		output[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
	{
		output[i] = file[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*deletefile(char *file)
{
	char	*buffer;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	if (!file)
		return (NULL);
	while (file[i] != '\n' && file[i])
		i++;
	if (file[i] == '\0')
	{
		free(file);
		return (NULL);
	}
	buffer = malloc((ft_strlen2(file) - i + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i++;
	while (file[i] != '\0')
		buffer[ii++] = file[i++];
	buffer[ii] = '\0';
	free(file);
	return (buffer);
}
