/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:17:41 by aharder           #+#    #+#             */
/*   Updated: 2025/03/03 16:17:46 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_env(t_commands *temp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (temp->command[i] != NULL)
	{
		j = ft_strlen(temp->command[i]);
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
	char	*value;
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
	char	*value;
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

char	**insert_files(char **command, int index)
{
	char	**filenames;
	char	**output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	filenames = get_filenames();
	output = malloc((array_size(filenames) + array_size(command) + 1) * sizeof(char *));
	while (i++ < index)
		output[i - 1] = ft_strdup(command[i - 1]);
	while (filenames[j] != NULL)
	{
		output[index + j] = ft_strdup(filenames[j]);
		j++;
	}
	j = j + index;
	index++;
	while (command[index] != NULL)
		output[j++] = ft_strdup(command[index++]);
	output[j] = NULL;
	free_split(filenames);
	free_split(command);
	return (output);
}
