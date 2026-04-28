#include "minishell.h"

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (!cmd->arguments)
		status = export_no_args(shell, cmd);
	else
		status = export_args(shell, cmd);
	shell->last_exit_status = 0;
	return (status);
}
