#include "minishell.h"

void	free_data(void *data)
{
	if (data)
		free(data);
}

void	free_array(void **arr_ptr)
{
	int	i;

	if (!arr_ptr)
		return ;
	i = 0;
	while (arr_ptr[i])
		free_null(&arr_ptr[i++]);
	free(arr_ptr);
}
