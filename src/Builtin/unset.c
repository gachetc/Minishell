#include "minishell.h"

static void	process_arg(t_shell *shell, t_list *arg)
{
	t_list	*env_node;

	if (!arg->data)
		return ;
	env_node = find_envvar_node(shell->envvar, (char *)arg->data);
	if (env_node)
		ft_lstdel_node(&shell->envvar, env_node, free_envv_struct);
}

static void	process_args(t_shell *shell, t_list *args)
{
	t_list	*next_arg;

	while (args)
	{
		next_arg = args->next;
		process_arg(shell, args);
		args = next_arg;
	}
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->arguments || !shell->envvar)
	{
		shell->last_exit_status = 0;
		return (0);
	}
	process_args(shell, cmd->arguments);
	shell->last_exit_status = 0;
	return (0);
}
