#include "minishell.h"

void	free_everything(t_shell *shell)
{
	if (shell)
	{
		free_input(shell);
		if (shell->envvar)
		{
			ft_lstclear(&(shell->envvar), free_envv_struct);
			shell->envvar = NULL;
		}
		if (shell->pids)
		{
			ft_lstclear(&(shell->pids), free_data);
			shell->pids = NULL;
		}
		free(shell);
	}
}
