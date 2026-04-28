#include "minishell.h"

void	error_and_exit(t_shell *shell, char *error_message)
{
	int		exit_status;

	exit_status = shell->last_exit_status;
	if (exit_status == 0)
		exit_status = EXIT_FAILURE;
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd(DEF, 2);
	ft_putstr_fd("\n", 2);
	free_everything(shell);
	exit(exit_status);
}
