#include "minishell.h"

int	update_or_add_env_var(t_shell *msh, char **str_array)
{
	t_list	*node_exists;
	t_envv	*envv_struct;

	if (!str_array[0] || !str_array[1])
		return (1);
	node_exists = find_envvar_node(msh->envvar, str_array[0]);
	if (!node_exists && str_array[1][0] == '\0')
		return (0);
	if (node_exists)
	{
		update_node_value(node_exists, str_array[1]);
		((t_envv *)node_exists->data)->is_exported = 1;
	}
	else
	{
		envv_struct = malloc(sizeof(t_envv));
		if (!envv_struct)
			return (free_and_set_error(str_array, msh));
		envv_struct->env_key = ft_strdup(str_array[0]);
		envv_struct->env_value = ft_strdup(str_array[1]);
		envv_struct->is_exported = 1;
		add_envv_to_dlist(msh, envv_struct);
	}
	return (0);
}

int	handle_no_quotes_error(char *arg_concat, char **str_array, t_shell *msh)
{
	free(arg_concat);
	free(str_array[0]);
	free(str_array);
	msh->last_exit_status = 1;
	return (1);
}

int	handle_str_array_removal(char *arg_concat, char **str_array, t_shell *msh)
{
	char	*no_quotes;

	no_quotes = remove_quotes(str_array[1]);
	if (!no_quotes)
		return (handle_no_quotes_error(arg_concat, str_array, msh));
	free(str_array[1]);
	str_array[1] = no_quotes;
	if (update_or_add_env_var(msh, str_array))
		return (1);
	free(str_array[0]);
	free(str_array[1]);
	free(str_array);
	free(arg_concat);
	msh->last_exit_status = 0;
	return (0);
}
