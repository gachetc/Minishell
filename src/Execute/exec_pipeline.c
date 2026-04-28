#include "minishell.h"

int	ft_lstindex(t_list *head, t_list *node)
{
	int	index;

	index = 0;
	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

void	execute_pipeline(t_shell *shell, t_exec_params params)
{
	t_list	*curr_cmd;
	int		num_cmds;
	int		num_pipes;
	int		**pipes;

	curr_cmd = shell->cmd_queue;
	num_cmds = ft_lstsize(curr_cmd);
	num_pipes = num_cmds - 1;
	params.shell = shell;
	params.num_pipes = num_pipes;
	params.num_cmds = num_cmds;
	if (num_pipes > 0)
		pipes = init_pipes(&params);
	else
		pipes = NULL;
	params.pipes = pipes;
	while (curr_cmd)
	{
		execute_command_wrapper(shell, curr_cmd, &params);
		reset_file_descriptors(shell);
		curr_cmd = curr_cmd->next;
	}
	if (num_pipes > 0)
		close_pipes(&params);
	get_pid_exit_status(shell, &shell->pids);
}

void	execute_command_wrapper(t_shell *shell, t_list \
		*curr_cmd, t_exec_params *params)
{
	t_cmd	*cmd_data;
	int		cmd_index;

	cmd_data = (t_cmd *)curr_cmd->data;
	params->cmd = cmd_data;
	if (!cmd_data || !cmd_data->command)
		return ;
	cmd_index = ft_lstindex(shell->cmd_queue, curr_cmd);
	params->cmd_index = cmd_index;
	if (ft_strcmp(cmd_data->command, "exit") == 0)
	{
		ft_exit(shell, cmd_data);
		return ;
	}
	if (ft_strstr(cmd_data->command, "/bin/") != NULL || \
	ft_strstr(cmd_data->command, "/usr/") != NULL)
		execute_command(shell, cmd_data, params);
	else if (cmd_is_builtin(cmd_data->command) && params->num_pipes == 0)
		execute_builtin(shell, cmd_data);
	else if (cmd_is_builtin(cmd_data->command))
		execute_builtin_with_pipes(shell, cmd_data, params);
	else
		execute_command(shell, cmd_data, params);
}
