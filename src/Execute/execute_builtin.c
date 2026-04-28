#include "minishell.h"

void	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->command, "env") == 0 || \
			ft_strcmp(cmd->command, "/usr/bin/env") == 0)
		status = ft_env(shell, cmd);
	else if (ft_strcmp(cmd->command, "pwd") == 0 || \
			ft_strcmp(cmd->command, "/bin/pwd") == 0)
		status = ft_pwd(shell, cmd);
	else if (ft_strcmp(cmd->command, "export") == 0 || \
			ft_strcmp(cmd->command, "/usr/bin/export") == 0)
		status = ft_export(shell, cmd);
	else if (ft_strcmp(cmd->command, "echo") == 0 || \
			ft_strcmp(cmd->command, "/bin/echo") == 0)
		status = ft_echo(shell, cmd);
	else if (ft_strcmp(cmd->command, "exit") == 0 || \
			ft_strcmp(cmd->command, "/bin/exit") == 0)
		status = ft_exit(shell, cmd);
	else if (ft_strcmp(cmd->command, "cd") == 0 || \
			ft_strcmp(cmd->command, "/bin/cd") == 0)
		status = ft_cd(shell, cmd);
	else if (ft_strcmp(cmd->command, "unset") == 0 || \
			ft_strcmp(cmd->command, "/usr/bin/unset") == 0)
		status = ft_unset(shell, cmd);
	shell->last_exit_status = status;
}
