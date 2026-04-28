#include "minishell.h"

char	**split_variables(char *envv)
{
	char	**cloned_substrs;

	if (!envv)
	{
		error("split_variables no envv", NULL);
		return (NULL);
	}
	cloned_substrs = ft_split_first(envv, '=');
	if (!cloned_substrs)
	{
		error("split_variables ft_split failed", NULL);
		return (NULL);
	}
	return (cloned_substrs);
}

t_envv	*put_str_in_envv_struct(char **cloned_substrs)
{
	t_envv	*envv_struct;

	if (!cloned_substrs || !*cloned_substrs)
		return (NULL);
	envv_struct = calloc_and_check_alloc(1, sizeof(t_envv), \
	"put_str_in_envv_struct");
	if (!envv_struct)
	{
		free_array((void **)cloned_substrs);
		error("clone_envv envv_struct malloc failed", NULL);
		return (NULL);
	}
	envv_struct->env_key = cloned_substrs[0];
	envv_struct->env_value = cloned_substrs[1];
	return (envv_struct);
}

void	add_envv_to_dlist(t_shell *shell, t_envv *s_envv)
{
	t_list	*new_node;

	if (!s_envv)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "clone_envv no envv_struct");
	}
	new_node = ft_lstnew(s_envv);
	if (!new_node)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "clone_envv new_node malloc error");
	}
	if (!shell->envvar)
		shell->envvar = new_node;
	else
		ft_lstadd_back(&shell->envvar, new_node);
}

void	process_single_envv(t_shell *shell, char *envv)
{
	char	**cloned_substrs;
	t_envv	*envv_struct;

	cloned_substrs = split_variables(envv);
	if (!cloned_substrs)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "clone_envv split_variables failed");
	}
	envv_struct = put_str_in_envv_struct(cloned_substrs);
	if (!envv_struct)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "clone_envv put_str_in_envv_struct failed");
	}
	add_envv_to_dlist(shell, envv_struct);
	free(cloned_substrs);
}

void	clone_envv_to_dlist(t_shell *shell, char **envv)
{
	if (!envv || !*envv)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "clone_envv no envv");
	}
	while (*envv)
	{
		process_single_envv(shell, *envv);
		envv++;
	}
}
