#include "minishell.h"

static void	close_unused_pipes(t_exec_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_pipes)
	{
		if (i != params->cmd_index - 1 && i != params->cmd_index)
		{
			close(params->pipes[i][0]);
			close(params->pipes[i][1]);
		}
		i++;
	}
}

void	setup_child_pipes(t_exec_params *params)
{
	if (params->cmd_index > 0)
	{
		if (dup2(params->pipes[params->cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(EXIT_FAILURE);
		}
		close(params->pipes[params->cmd_index - 1][0]);
		close(params->pipes[params->cmd_index - 1][1]);
	}
	if (params->cmd_index < params->num_pipes)
	{
		if (dup2(params->pipes[params->cmd_index][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(EXIT_FAILURE);
		}
		close(params->pipes[params->cmd_index][0]);
		close(params->pipes[params->cmd_index][1]);
	}
	close_unused_pipes(params);
}

static void	handle_parent_process(t_shell *shell, t_exec_params \
		*params, pid_t pid)
{
	pid_t	*new_pid;
	t_list	*new_node;

	new_pid = malloc(sizeof(pid_t));
	if (!new_pid)
		exit(EXIT_FAILURE);
	*new_pid = pid;
	new_node = ft_lstnew(new_pid);
	if (!new_node)
		exit(EXIT_FAILURE);
	ft_lstadd_back(&shell->pids, new_node);
	if (params->cmd_index > 0)
		close(params->pipes[params->cmd_index - 1][0]);
	if (params->cmd_index < params->num_pipes)
		close(params->pipes[params->cmd_index][1]);
}

void	execute_builtin_with_pipes(t_shell *shell, t_cmd \
		*cmd, t_exec_params *params)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		reset_signal_handlers();
		setup_child_pipes(params);
		handle_redirections(cmd, shell);
		execute_builtin(shell, cmd);
		exit(shell->last_exit_status);
	}
	else
	{
		handle_parent_process(shell, params, pid);
	}
}
