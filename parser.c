/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:23:35 by aharder           #+#    #+#             */
/*   Updated: 2025/02/17 16:49:24 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *source, int size)
{
	unsigned char	*dest2;
	unsigned char	*source2;
	int				i;

	i = 0;
	dest2 = (unsigned char *) dest;
	source2 = (unsigned char *) source;
	while (i < size)
	{
		dest2[i] = source2[i];
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

typedef struct s_node
{
	char	*cmd;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_token
{
	int	type;
	char	*value;
}	t_token;

typedef struct s_commands
{
	char	*command;
	struct s_command	*next;
}	t_commands;

int	cmp(char c)
{
	int	i;
	char	list[] = { '|', '<', '>', '\0' };

	i = 0;
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
}

int	splitlen(const char *s)
{
	int	i;
	int	split;

	i = 0;
	split = 0;
	while (s[i] != '\0')
	{
		while (cmp(s[i]) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			split++;
		while (!cmp(s[i]) && s[i] != '\0')
			i++;
	}
	return (split);
}

char	**multi_split(char *s)
{
	int	i[4];
	int	buffer;
	char	**output;

	i[0] = 0;
	i[2] = 0;
	output = malloc((splitlen(s) + 1) * sizeof(char *));
	if (!output)
		return NULL;
	while (s[i[0]] != '\0')
	{
		while (cmp(s[i[0]]) == 1 && s[i[0]] != '\0')
			i[0]++;
		if (s[i[0]] == '\0')
			break;
		i[1] = i[0];
		while (cmp(s[i[1]]) == 0 && s[i[1]] != '\0')
			i[1]++;
		output[i[2]] = malloc((i[1] - i[0] + 1) * sizeof(char));
		if (!output[i[2]])
			return NULL;
		i[3] = 0;
		while (i[0] < i[1])
			output[i[2]][i[3]++] = s[i[0]++];
		output[i[2]][i[3]] = '\0';
		i[2]++;
	}
	output[i[2]] = NULL;
	return (output);
}
int	main(int argc, char *argv[])
{
	int	i;
	char	**splitted;
	t_commands	commands;
	if (argc < 2)
		return (printf("Erreur: input\n"));
	i = 0;
	splitted = multi_split(argv[1]);
	while (splitted[i] != NULL)
	{
		printf("%s\n", splitted[i]);
		i++;
	}
}
