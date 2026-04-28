#include "minishell.h"

static void	handle_heredoc(t_cmd *cmd, t_list **token_ptr, t_shell *shell)
{
	char	*delimiter;

	if (!(*token_ptr)->next)
	{
		error("syntax error near unexpected token `newline'", NULL);
		shell->last_exit_status = 258;
		return ;
	}
	*token_ptr = (*token_ptr)->next;
	delimiter = remove_quotes((char *)(*token_ptr)->data);
	cmd->heredoc_delimiter = ft_strdup(delimiter);
	if (cmd->heredoc_delimiter == NULL)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	cmd->heredoc_data = read_heredoc(delimiter);
	free(delimiter);
}

static void	handle_input(t_cmd *cmd, t_list **token_ptr, t_shell *shell)
{
	char	*input_file;

	if (!(*token_ptr)->next)
	{
		error("syntax error near unexpected token `newline'", NULL);
		shell->last_exit_status = 258;
		return ;
	}
	*token_ptr = (*token_ptr)->next;
	input_file = remove_quotes((char *)(*token_ptr)->data);
	cmd->input_file = input_file;
}

static void	handle_output(t_cmd *cmd, t_list **token_ptr, t_shell *shell)
{
	int		fd;
	char	*output_file;

	fd = -1;
	if (!(*token_ptr)->next)
	{
		shell->last_exit_status = 258;
		return (error("syntax error near unexpected token `newline'", NULL));
	}
	*token_ptr = (*token_ptr)->next;
	cmd->is_append = false;
	output_file = remove_quotes((char *)(*token_ptr)->data);
	if (cmd->output_file)
		free_null((void **)&(cmd->output_file));
	cmd->output_file = output_file;
	if (ft_strcmp((char *)(*token_ptr)->prev->data, ">>") == 0)
	{
		cmd->is_append = true;
		fd = open(cmd->output_file, O_WRONLY | O_CREAT \
					| O_APPEND, 0644);
	}
	else if (cmd->is_append != true)
		fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("open failed", cmd->output_file);
	else if (fd > 0)
		close(fd);
}

void	handle_redirection(t_cmd *cmd, t_list **token_ptr, t_shell *shell)
{
	char	*token_data;

	token_data = (char *)(*token_ptr)->data;
	if (ft_strcmp(token_data, "<") == 0 && ft_strlen(token_data) == 1)
		handle_input(cmd, token_ptr, shell);
	else if (ft_strncmp(token_data, "<<", 2) == 0 && ft_strlen(token_data) == 2)
		handle_heredoc(cmd, token_ptr, shell);
	else if ((ft_strcmp(token_data, ">") == 0 || \
	ft_strcmp(token_data, ">>") == 0) && ((ft_strlen(token_data) == 1) || \
	ft_strlen(token_data) == 2))
		handle_output(cmd, token_ptr, shell);
}

void	preprocess_redirections(t_cmd *cmd, t_list **curr_token_ptr, \
		t_shell *shell)
{
	t_list	*token;
	t_list	*last_token;
	int		i;
	int		nb_tokens;
	int		nb_total_cmds;

	i = 0;
	last_token = NULL;
	nb_tokens = 0;
	nb_total_cmds = ft_lstsize(*curr_token_ptr);
	token = *curr_token_ptr;
	while (token && is_redirect((char *)token->data))
	{
		handle_redirection(cmd, &token, shell);
		i++;
		if (token)
		{
			last_token = token;
			nb_tokens++;
			token = token->next;
		}
	}
	*curr_token_ptr = token;
	if (i > 0 && (nb_tokens * 2 == nb_total_cmds))
		check_and_free_cmd_struct(cmd, last_token);
}
