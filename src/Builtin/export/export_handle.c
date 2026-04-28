#include "minishell.h"

int	handle_no_equal_sign(t_shell *msh, char *arg_concat)
{
	t_list	*node_exists;
	t_envv	*envv_struct;

	node_exists = find_envvar_node(msh->envvar, arg_concat);
	if (node_exists)
		((t_envv *)node_exists->data)->is_exported = 1;
	else
	{
		envv_struct = malloc(sizeof(t_envv));
		if (!envv_struct)
		{
			free(arg_concat);
			msh->last_exit_status = 1;
			return (1);
		}
		envv_struct->env_key = ft_strdup(arg_concat);
		envv_struct->env_value = NULL;
		envv_struct->is_exported = 1;
		add_envv_to_dlist(msh, envv_struct);
	}
	free(arg_concat);
	msh->last_exit_status = 0;
	return (0);
}

int	handle_syntax_check(t_shell *msh, char *arg_concat, int syntax_check)

{
	if (syntax_check == -1 || syntax_check == 1)
	{
		free(arg_concat);
		if (syntax_check == -1)
			msh->last_exit_status = 1;
		else
			msh->last_exit_status = 0;
		return (1);
	}
	return (0);
}

int	handle_str_array(t_shell *msh, char **str_array, char *arg_concat)
{
	if (!str_array || !str_array[0])
	{
		free(arg_concat);
		if (str_array)
			free(str_array);
		msh->last_exit_status = 1;
		return (1);
	}
	if (ft_strlen(str_array[0]) == 0)
	{
		error("not a valid identifier", str_array[1]);
		free(arg_concat);
		free(str_array[0]);
		free(str_array[1]);
		free(str_array);
		msh->last_exit_status = 1;
		return (1);
	}
	return (0);
}

int	free_and_set_error(char **str_array, t_shell *msh)
{
	free(str_array[0]);
	free(str_array[1]);
	free(str_array);
	msh->last_exit_status = 1;
	return (1);
}
