#include "minishell.h"

void	execute_command(t_shell *shell, t_cmd *cmd, t_exec_params *params)
{
	char			**env;
	char			**args;
	pid_t			pid;

	env = convert_envvar_to_array(shell);
	args = put_args_in_array(cmd);
	params->shell = shell;
	params->cmd = cmd;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execute_command_child(params, env, args, shell);
	else
		execute_command_parent(params, pid);
	free_exec_arrays(env, args);
}

char	*get_command_path(t_shell *shell, char *command)
{
	char	*path;

	if (has_path(command))
	{
		path = ft_strdup(command);
		if (!path)
		{
			shell->last_exit_status = 1;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		path = get_path(shell, command);
		if (!path)
		{
			error("Command not found", command);
			shell->last_exit_status = 127;
			exit(127);
		}
	}
	return (path);
}

static void	exec_command(t_exec_params *params, char **env, char **args, \
t_shell *shell)
{
	char	*path;

	path = NULL;
	if (ft_strstr(args[0], "/bin/") != NULL || ft_strstr(args[0], "/usr/") \
	!= NULL)
	{
		handle_bin_paths(args, shell, params);
		path = args[0];
	}
	else
		path = get_command_path(params->shell, args[0]);
	check_command_access(path, shell);
	execve(path, args, env);
	perror("execve");
	free(path);
	free_exec_arrays(env, args);
	exit(EXIT_FAILURE);
}

void	execute_command_child(t_exec_params *params, char **env, char **args, \
t_shell *shell)
{
	reset_signal_handlers();
	setup_child_pipes(params);
	handle_redirections(params->cmd, shell);
	if (cmd_is_builtin(params->cmd->command))
	{
		execute_builtin(params->shell, params->cmd);
		exit(params->shell->last_exit_status);
	}
	exec_command(params, env, args, shell);
}

void	execute_command_parent(t_exec_params *params, pid_t pid)
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
	ft_lstadd_back(&params->shell->pids, new_node);
	if (params->cmd_index > 0)
		close(params->pipes[params->cmd_index - 1][0]);
	if (params->cmd_index < params->num_pipes)
		close(params->pipes[params->cmd_index][1]);
}
