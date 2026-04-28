#include "minishell.h"

static void	handle_input_redirection(t_cmd *cmd)
{
	int	in_fd;

	if (cmd->input_file)
	{
		in_fd = open(cmd->input_file, O_RDONLY);
		if (in_fd < 0)
		{
			error("failed to open input_file", cmd->input_file);
			exit(EXIT_FAILURE);
		}
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input_file");
			close(in_fd);
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
}

static void	handle_heredoc_redirection(t_cmd *cmd, t_shell *shell)
{
	int		pipe_fd[2];
	char	*evaluated_data;

	if (cmd->heredoc_data && pipe(pipe_fd) != -1)
	{
		evaluated_data = evaluate_envvars(cmd->heredoc_data, shell);
		if (evaluated_data)
		{
			write(pipe_fd[1], evaluated_data, strlen(evaluated_data));
			free(evaluated_data);
		}
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			close(pipe_fd[0]);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[0]);
	}
	shell->is_heredoc = false;
}

static void	handle_output_redirection(t_cmd *cmd)
{
	int	out_fd;

	if (cmd->output_file)
	{
		if (cmd->is_append)
			out_fd = open(cmd->output_file, O_WRONLY | O_CREAT \
					| O_APPEND, 0644);
		else
			out_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0 || dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("open/dup2 output_file");
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
}

void	handle_redirections(t_cmd *cmd, t_shell *shell)
{
	if (cmd->input_file)
		handle_input_redirection(cmd);
	if (cmd->heredoc_data)
	{
		shell->is_heredoc = true;
		handle_heredoc_redirection(cmd, shell);
	}
	if (cmd->output_file)
		handle_output_redirection(cmd);
}
