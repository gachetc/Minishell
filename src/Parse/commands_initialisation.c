#include "minishell.h"

static void	fill_command_element(t_cmd *cmd, t_list **curr_token_ptr)
{
	cmd->is_grep = false;
	if ((char *)(*curr_token_ptr)->data == NULL)
		error_exit("fill_command_element no token");
	cmd->command = ft_strdup((char *)(*curr_token_ptr)->data);
	if (!cmd->command)
		error_exit("extract_commands strdup error");
	if (ft_strcmp(cmd->command, "grep") == 0)
		cmd->is_grep = true;
}

t_cmd	*initialize_cmd(t_list **curr_token_ptr, t_shell *shell)
{
	t_cmd	*cmd;

	if (!curr_token_ptr || !*curr_token_ptr)
	{
		shell->last_exit_status = 258;
		return (NULL);
	}
	cmd = calloc_and_check_alloc(1, sizeof(t_cmd), \
	"extract_commands cmd malloc error");
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->is_append = false;
	fill_command_element(cmd, curr_token_ptr);
	return (cmd);
}

t_cmd	*initialize_cmd_struct(t_list **curr_token_ptr, t_shell *shell)
{
	t_cmd	*cmd_struct;

	cmd_struct = calloc_and_check_alloc(1, sizeof(t_cmd), \
	"extract_commands cmd malloc error");
	cmd_struct->in_fd = STDIN_FILENO;
	cmd_struct->out_fd = STDOUT_FILENO;
	preprocess_redirections(cmd_struct, curr_token_ptr, shell);
	return (cmd_struct);
}

void	add_args_to_cmd(t_shell *shell, t_cmd *cmd, char *data)
{
	char	*arg;
	char	*arg_no_quotes;
	t_list	*arg_node;

	arg_no_quotes = NULL;
	shell->contains_export = false;
	arg = ft_strdup(data);
	if (ft_strcmp(cmd->command, "export") == 0)
		shell->contains_export = true;
	if ((shell->contains_echo == false || cmd->is_grep == true) && \
	shell->contains_export == false)
	{
		arg_no_quotes = remove_quotes(arg);
		free(arg);
		arg = arg_no_quotes;
		cmd->is_grep = false;
	}
	arg_node = ft_lstnew(arg);
	if (!arg_node)
	{
		free_cmd_struct(cmd);
		shell->last_exit_status = 1;
		error_and_exit(shell, "fill_cmd_struct error");
	}
	ft_lstadd_back(&(cmd->arguments), arg_node);
}
