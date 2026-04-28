#include "minishell.h"

static char	*rejoin_env_strings(t_list *node)
{
	t_envv	*envv_struct;
	int		key_len;
	int		value_len;
	char	*string;

	envv_struct = (t_envv *)node->data;
	if (!envv_struct->env_value)
	{
		string = ft_strdup(envv_struct->env_key);
		return (string);
	}
	key_len = ft_strlen(envv_struct->env_key);
	value_len = ft_strlen(envv_struct->env_value);
	string = (char *)calloc_and_check_alloc(key_len + value_len + 2, \
			sizeof(char), "rejoin_env_strings calloc error");
	ft_strcpy(string, envv_struct->env_key);
	string[key_len] = '=';
	ft_strcpy(&string[key_len + 1], envv_struct->env_value);
	return (string);
}

char	**convert_envvar_to_array(t_shell *shell)
{
	char	**array;
	int		i;
	int		length;
	t_list	*curr_node;

	i = 0;
	curr_node = shell->envvar;
	length = ft_lstsize(shell->envvar);
	array = (char **)calloc_and_check_alloc(length + 1, sizeof(char *), \
		"convert_envvar_to_array error");
	while (i < length)
	{
		array[i++] = rejoin_env_strings(curr_node);
		curr_node = curr_node->next;
	}
	return (array);
}
