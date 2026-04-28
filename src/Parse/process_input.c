#include "minishell.h"

static bool	is_operator(char *str)
{
	return (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0);
}

static int	check_pipe_errors(t_list *tokens)
{
	t_list	*curr;

	if (ft_strcmp((char *)tokens->data, "|") == 0)
	{
		error("syntax error near unexpected token", "|");
		return (1);
	}
	curr = tokens;
	while (curr)
	{
		if (ft_strcmp((char *)curr->data, "|") == 0 && !curr->next)
		{
			error("syntax error near unexpected token", "|");
			return (1);
		}
		if (ft_strcmp((char *)curr->data, "|") == 0 && curr->next
			&& ft_strcmp((char *)curr->next->data, "|") == 0)
		{
			error("syntax error near unexpected token", "|");
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	check_redir_errors(t_list *tokens)
{
	t_list	*curr;
	char	*data;

	curr = tokens;
	while (curr)
	{
		data = (char *)curr->data;
		if (is_redirect(data))
		{
			if (!curr->next)
			{
				error("syntax error near unexpected token", "newline");
				return (1);
			}
			if (is_operator((char *)curr->next->data))
			{
				error("syntax error near unexpected token",
					(char *)curr->next->data);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

static void	set_shell_flags(t_shell *shell)
{
	t_list	*curr;

	shell->contains_pipe = false;
	shell->contains_echo = false;
	curr = shell->tokens;
	while (curr)
	{
		if (ft_strcmp((char *)curr->data, "|") == 0)
			shell->contains_pipe = true;
		curr = curr->next;
	}
	curr = shell->tokens;
	while (curr)
	{
		if (!is_redirect((char *)curr->data))
		{
			if (ft_strcmp((char *)curr->data, "echo") == 0)
				shell->contains_echo = true;
			break ;
		}
		if (curr->next)
			curr = curr->next->next;
		else
			break ;
	}
}

int	validate_tokens(t_shell *shell)
{
	if (!shell->tokens)
		return (1);
	if (check_pipe_errors(shell->tokens))
	{
		shell->last_exit_status = 2;
		free_tokens(shell);
		return (1);
	}
	if (check_redir_errors(shell->tokens))
	{
		shell->last_exit_status = 2;
		free_tokens(shell);
		return (1);
	}
	set_shell_flags(shell);
	return (0);
}

void	process_input(t_shell *shell)
{
	if (add_tokens_to_list(shell) == 1)
		return ;
	if (validate_tokens(shell) == 1)
		return ;
	extract_commands(shell);
	process_fds(shell);
}
