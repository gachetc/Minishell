#include "minishell.h"

void	free_input(t_shell *shell)
{
	if (shell->cmd_queue)
	{
		ft_lstclear(&(shell->cmd_queue), free_cmd_struct);
		shell->cmd_queue = NULL;
	}
	if (shell->tokens)
	{
		ft_lstclear(&(shell->tokens), free_data);
		shell->tokens = NULL;
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
}
