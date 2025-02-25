/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:00:20 by aharder           #+#    #+#             */
/*   Updated: 2025/02/25 16:28:11 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_var_bundle
{
	int	i;
	int	j;
	int	y;
	int	s_quotes;
	int	d_quotes;
}	t_var_bundle;

char	**first_split(char *s)
{
	t_var_bundle	var;
	char	**output;

	assign_start_value(&var);
	output = malloc((first_split_size(s) + 1) * sizeof(char *));
	while (s[var.i] != '\0')
	{
		i = srch_operator(&s[var.i]);
		var.j = var.i;
		while ((srch_operator == 0 || var.s_quotes || var.d_quotes) && s[var.i] != '\0')
		{
			if (!var.s_quotes && s[var.j] == '"')
				var.d_quotes = !var.d_quotes;
			else if (!var.d_quotes && s[var.j] == '\'')
				var.s_quotes = !var.s_quotes;
			var.j++;	
		}
		output[var.y] = crop_str(s, var.i, var.j);
		var.y++;
	}
	if (var.d_quotes || var.s_quotes)
		return (perror_and_free(output));
	output[var.i] = NULL;
	return (output);
}
