#include "../../include/minishell.h"

int	arg_val_has_valid_chars(char *arg)
{
	int	i;

	if (!ft_strchr(arg, '='))
		return (1);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		if (arg[i] == '!' || arg[i] == ')' || arg[i] == '(')
			return (0);
		i++;
	}
	return (1);
}

int	arg_var_has_valid_chars(char *arg)
{
	int	i;

	i = 0;
	
	if (arg[0] && (arg[0] == '=' || ft_isdigit(arg[0])))
		return (0);
	while (arg[i] && arg[i]!= '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (arg[i] == '+' && (!arg[i + 1] || arg[i + 1] == '='))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

/*
int	unset_arg_var_has_valid_chars(char *arg)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (arg[0] && (arg[0] == '=' || ft_isdigit(arg[0])))
		return (0);
	while (arg[i] && arg[i]!= '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (arg[i] == '+' && (!arg[i + 1] || arg[i + 1] == '='))
				return (1);
			else
				return (0);
		}
		i++;
	}
	if (arg[i] == '=' && arg[i + 1] == '\0')
		res = 0;
	return (res);
}
*/