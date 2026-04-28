#include "minishell.h"

static void	handle_heredoc_fd(t_cmd *cmd_data)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		error("failure creating pipe", NULL);
		exit(EXIT_FAILURE);
	}
	write(fds[1], cmd_data->heredoc_data, ft_strlen(cmd_data->heredoc_data));
	close(fds[1]);
	if (cmd_data->in_fd != STDIN_FILENO)
		close(cmd_data->in_fd);
	cmd_data->in_fd = fds[0];
}

static void	process_input_file(t_cmd *cmd_data)
{
	int	in_fd;

	if (cmd_data->input_file)
	{
		in_fd = open(cmd_data->input_file, O_RDONLY);
		if (in_fd == -1)
			return ;
		if (cmd_data->in_fd != STDIN_FILENO)
			close(cmd_data->in_fd);
		cmd_data->in_fd = in_fd;
	}
}

static void	process_output_file(t_cmd *cmd_data)
{
	int	out_fd;
	int	open_flags;

	if (cmd_data->output_file)
	{
		open_flags = O_CREAT | O_WRONLY;
		if (cmd_data->is_append)
			open_flags |= O_APPEND;
		else
			open_flags |= O_TRUNC;
		out_fd = open(cmd_data->output_file, open_flags, 0644);
		if (out_fd == -1)
			return (perror("open output_file"));
		if (cmd_data->out_fd != STDOUT_FILENO)
			close(cmd_data->out_fd);
		cmd_data->out_fd = out_fd;
		if (dup2(cmd_data->out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output_file");
			close(out_fd);
			exit(EXIT_FAILURE);
		}
	}
}

static void	process_redir_fds(t_shell *shell)
{
	t_list	*curr_cmd;
	t_cmd	*cmd_data;

	curr_cmd = shell->cmd_queue;
	if (curr_cmd == NULL)
		return ;
	while (curr_cmd)
	{
		cmd_data = curr_cmd->data;
		if (cmd_data->heredoc_data)
			handle_heredoc_fd(cmd_data);
		process_input_file(cmd_data);
		process_output_file(cmd_data);
		curr_cmd = curr_cmd->next;
	}
}

void	process_fds(t_shell *shell)
{
	process_redir_fds(shell);
}
