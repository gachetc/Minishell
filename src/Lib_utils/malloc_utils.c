#include "minishell.h"

void	*malloc_and_check_alloc(size_t bytes, char *error_message)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
		error_exit(error_message);
	return (result);
}

void	*calloc_and_check_alloc(size_t number, size_t size, char *error_message)
{
	void	*result;

	result = ft_calloc(number, size);
	if (!result)
		error_exit(error_message);
	return (result);
}
