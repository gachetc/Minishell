#include "minishell.h"

void	free_tokens(t_shell *shell)
{
	ft_lstclear(&(shell->tokens), free_data);
	shell->tokens = NULL;
}
