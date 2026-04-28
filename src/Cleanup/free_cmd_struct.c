#include "minishell.h"

void	free_arguments(t_list *arguments)
{
	t_list	*curr_arg;
	t_list	*next_arg;

	curr_arg = arguments;
	while (curr_arg)
	{
		next_arg = curr_arg->next;
		if (curr_arg->data)
			free(curr_arg->data);
		free(curr_arg);
		curr_arg = next_arg;
	}
}

void	free_cmd_struct(void *data)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)data;
	if (!cmd)
		return ;
	if (cmd->arguments)
		free_arguments(cmd->arguments);
	if (cmd->command)
		free(cmd->command);
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	if (cmd->heredoc_data)
		free(cmd->heredoc_data);
	free(cmd);
}
