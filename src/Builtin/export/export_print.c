#include "minishell.h"

static void	print_variable(t_envv *data, int out_fd)
{
	ft_putstr_fd("declare -x ", out_fd);
	ft_putstr_fd(data->env_key, out_fd);
	if (data->env_value == NULL)
	{
		ft_putstr_fd("\n", out_fd);
	}
	else
	{
		ft_putstr_fd("=\"", out_fd);
		ft_putstr_fd(data->env_value, out_fd);
		ft_putstr_fd("\"\n", out_fd);
	}
}

static void	process_variables(t_list *cloned_list, int out_fd)
{
	t_list	*curr_variable;
	t_envv	*data;

	curr_variable = cloned_list;
	while (curr_variable)
	{
		data = (t_envv *)curr_variable->data;
		print_variable(data, out_fd);
		curr_variable = curr_variable->next;
	}
}

int	export_no_args(t_shell *msh, t_cmd *cmd)
{
	t_list	*cloned_list;

	cloned_list = clone_list(msh->envvar);
	sort_list(&cloned_list);
	process_variables(cloned_list, cmd->out_fd);
	free_cloned_list(cloned_list);
	msh->last_exit_status = 0;
	return (0);
}
