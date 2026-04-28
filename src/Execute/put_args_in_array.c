#include "minishell.h"

char	**put_args_in_array(t_cmd *cmd_struct)
{
	char	**array;
	t_list	*args;
	int		i;
	int		length;

	args = cmd_struct->arguments;
	length = ft_lstsize(args);
	array = calloc_and_check_alloc(length + 2, sizeof(char *), \
		"put_args_in_array error");
	array[0] = (char *)cmd_struct->command;
	i = 1;
	while (i <= length)
	{
		array[i++] = (char *)args->data;
		args = args->next;
	}
	return (array);
}
