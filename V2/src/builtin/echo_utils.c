#include "../../include/minishell.h"           

int	count_strings_pointer(char ***array_ptr)
{
	int count = 0;
    
    // Check if pointer to array is NULL
	if (array_ptr == NULL)
		return 0;    
    // Get the actual array
	char **array = *array_ptr;
    // Check if array itself is NULL
	if (array == NULL)
		return 0;
    // Count until NULL terminator is found

	while (array[count] != NULL)
	{
		count++;
	}
	return count;
}

void	ft_print_array_of_strings(char **array, int size)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		ft_putstr_fd("array[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("]: ", 1);
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(size, 1);
		ft_putchar_fd('\n', 1);
		//printf("array[%d]: %s %d\n", i, array[i], size);
		i++;
	}
} 

int	size_of_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*src;
	unsigned char	*dst;
	void		*new_ptr;
	size_t		copy_size;
	size_t		i;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	printf("old & new_size in my_realloc: %ld %ld\n", old_size, new_size);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	i = 0;
	while (i < copy_size)
	{
		dst[i] = src[i];
		i++;
	}
	return (new_ptr);
}

int	insert_string(char ***array, int *size, const char *str, int position)
{
	//char	**new_array;
	char	*new_str;
	int	i;

	if (array == NULL || size == NULL || str == NULL || position < 0 || position > *size)
		return (-1);
	//printf("array[0]: %s, size: %d, str: %s, position: %d\n", (*array)[0], *size, str, position);
	new_str = strdup(str);
	if (new_str == NULL)
		return (-1);
	/*
	new_array = my_realloc(*array, (*size) * sizeof(char *), (*size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		free(new_str);
		return (-1);
	}
	*array = new_array;
	*/
	i = *size;
	while (i > position) 
	{
		(*array)[i] = (*array)[i - 1];
		//printf("i: %d (*array)[i]: %s (*array)[i - 1]: %s i - 1: %d\n", i, (*array)[i], (*array)[i - 1], i - 1);
		i--;
	}
	(*array)[position] = new_str;
	//ft_free_array_size(new_array, (*size + 1));
	//free((*array)[*size + 1]);
	(*size)++;
	return (0);
}

void	ft_free_array_size(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	create_new_array(char ***array, char *arg, int index)
{
	//char	**result;
	char	**new_intermediate_array;
	int	i;
	int	size;
	int	size_new_array;
	//int	current_size;

	size = count_strings_pointer(array);
	//printf("size in create new array: %d\n", size);
	new_intermediate_array = ft_split(arg, ' ');
	size_new_array = size_of_array(new_intermediate_array);
	//ft_print_array_of_strings(new_intermediate_array, size_new_array);
	i = 0;
	while (i < size_new_array)
	{
		insert_string(array, &size, new_intermediate_array[i], index);
		i++;
		index++;
	}
	ft_free_array_size(new_intermediate_array, size_new_array);
	desert_string(array, &size, arg, index);
	return (size_new_array);
}

int	desert_string(char ***array, int *size, const char *str, int position)
{
	char	**current_array;
	int	i;
	
	(void)str;
	if (array == NULL || *array == NULL || size == NULL || *size <= 0 || position < 0 || position > *size)
		return (-1);
	i = 0;
	while (i < *size)
	{
		printf("array[0]: %s, size: %d, str: %s, position: %d\n", (*array)[i], *size, str, position);
		i++;
	}
	current_array = *array;
	free(current_array[position]);
	printf("position: %d size: %d\n", position, *size);
	i = position;
	while (i < *size - 1)
	{
		current_array[i] = current_array[i + 1];
		i++;
	}
	if (position == *size - 1)
		current_array[position] = NULL;
	current_array[i] = NULL;
	//printf(" i - 1 %s %d\n", current_array[i - 1], i - 1);
	//printf("   i %s %d\n", current_array[i], i);
	//printf("     i + 1%s\n", current_array[i + 1]);
	(*size)--;
	return (0);
}

/*
int	delete_old_string(char ***array, char *arg, int pos)
{
	int	size;

	//ft_putstr_fd("nous sommes ici\n", 1);
	size = count_strings_pointer(array);
	ft_putnbr_fd(size, 1);
	//ft_putstr_fd(" prev nb is size in delete old string\n", 1);
	return (desert_string(array, &size, arg, pos));
}
*/

void	echo_check(char ***args)
{
	int	size;
	int	i;
	int	jump;
	
	size = count_strings_pointer(args);
	i = 0;
	while (i < size)
	{
		if (there_is_space((*args)[i]))
		{
			jump = create_new_array(args, (*args)[i], i);
			i = i + jump - 1;
			size = size + jump - 1;
		}
		i++;		
	}
}