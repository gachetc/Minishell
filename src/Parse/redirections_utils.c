#include "minishell.h"

void	process_redirections(t_cmd *cmd, t_list **token_ptr, t_shell *shell)
{
	t_list	*token;

	token = *token_ptr;
	while (token && ft_strcmp((char *)token->data, "|") != 0)
	{
		if (is_redirect((char *)token->data))
		{
			if (token->prev == NULL && token->next == NULL)
			{
				error("syntax error near unexpected token `newline'", NULL);
				shell->last_exit_status = 258;
				break ;
			}
			else if (token->next)
				handle_redirection(cmd, &token, shell);
			else
				break ;
		}
		else
			token = token->next;
	}
	if (token && ft_strcmp((char *)token->data, "|") == 0)
		token = token->next;
	*token_ptr = token;
}

void	copy_redirections(t_cmd *src, t_cmd *dest)
{
	if (!src || !dest)
		return ;
	if (src->input_file)
	{
		free(dest->input_file);
		dest->input_file = ft_strdup(src->input_file);
	}
	if (src->output_file)
	{
		free(dest->output_file);
		dest->output_file = ft_strdup(src->output_file);
	}
	if (src->heredoc_delimiter)
	{
		free(dest->heredoc_delimiter);
		dest->heredoc_delimiter = ft_strdup(src->heredoc_delimiter);
	}
	if (src->heredoc_data)
	{
		free(dest->heredoc_data);
		dest->heredoc_data = ft_strdup(src->heredoc_data);
	}
	dest->is_append = src->is_append;
}

void	check_and_free_cmd_struct(t_cmd *cmd, t_list *last_token)
{
	if (last_token && ((cmd->output_file && ft_strcmp(cmd->output_file, \
	(char *)last_token->data) == 0) || (cmd->input_file && \
	ft_strcmp(cmd->input_file, (char *)last_token->data) == 0) || \
	(cmd->heredoc_delimiter && ft_strcmp(cmd->heredoc_delimiter, \
	(char *)last_token->data) == 0)) && ft_strcmp((char *)last_token->data, \
	"|") != 0)
		free_cmd_struct(cmd);
}
