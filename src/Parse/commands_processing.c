#include "minishell.h"

static t_cmd	*fill_cmd_struct(t_shell *shell, t_list **curr_token_ptr)
{
	t_cmd	*cmd;
	t_list	*token;

	cmd = initialize_cmd(curr_token_ptr, shell);
	if (!cmd)
		return (NULL);
	token = (*curr_token_ptr)->next;
	while (token && !is_redirect((char *)token->data) && \
	ft_strcmp((char *)token->data, "|") != 0)
	{
		add_args_to_cmd(shell, cmd, (char *)token->data);
		token = token->next;
	}
	process_redirections(cmd, &token, shell);
	*curr_token_ptr = token;
	return (cmd);
}

char	*remove_cmd_quotes(const char *cmd, t_shell *shell)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(cmd);
	shell->no_quote = (char *)malloc(len + 1);
	shell->first_quote = '\0';
	if (!shell->no_quote)
		return (NULL);
	copy_until_quote(cmd, &i, &j, shell);
	if (shell->first_quote)
		copy_after_quote(cmd, &i, &j, shell);
	else
	{
		while (cmd[i])
			shell->no_quote[j++] = cmd[i++];
	}
	shell->no_quote[j] = '\0';
	return (shell->no_quote);
}

int	add_cmd_to_list(t_shell *shell, t_cmd *cmd_struct)
{
	t_list	*new_node;
	char	*arg_no_quotes;

	if (!cmd_struct)
	{
		shell->last_exit_status = 258;
		return (1);
	}
	arg_no_quotes = remove_cmd_quotes(cmd_struct->command, shell);
	free(cmd_struct->command);
	cmd_struct->command = arg_no_quotes;
	new_node = ft_lstnew(cmd_struct);
	if (!new_node)
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "extract_command new_node malloc error");
	}
	ft_lstadd_back(&(shell->cmd_queue), new_node);
	return (0);
}

static	t_cmd	*process_command(t_shell *shell, t_list **curr_token_ptr, \
t_cmd *cmd_struct)
{
	t_cmd	*cmd_from_struct;

	cmd_from_struct = NULL;
	if (!curr_token_ptr || !*curr_token_ptr)
	{
		shell->last_exit_status = 258;
		return (NULL);
	}
	if (*curr_token_ptr)
	{
		cmd_from_struct = fill_cmd_struct(shell, curr_token_ptr);
		if (cmd_from_struct)
		{
			copy_redirections(cmd_struct, cmd_from_struct);
			free_cmd_struct(cmd_struct);
			cmd_struct = cmd_from_struct;
		}
	}
	return (cmd_struct);
}

void	extract_commands(t_shell *shell)
{
	t_list	*curr_token;
	t_cmd	*cmd_struct;

	curr_token = shell->tokens;
	if (!curr_token)
		return ;
	while (curr_token)
	{
		cmd_struct = initialize_cmd_struct(&curr_token, shell);
		cmd_struct = process_command(shell, &curr_token, cmd_struct);
		if (add_cmd_to_list(shell, cmd_struct) == 1)
			break ;
		if (!cmd_struct && ft_strstr(shell->input, "echo") == NULL)
		{
			error("extract_command missing command", NULL);
			shell->last_exit_status = 258;
			break ;
		}
		shell->num_of_cmds++;
	}
	free_tokens(shell);
}
