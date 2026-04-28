#include "minishell.h"

static void	increment_shlvl(t_shell *shell)
{
	t_list	*node;
	t_envv	*envv_struct;
	int		level;
	char	*new_value;

	if (!shell->envvar)
		return ;
	node = find_envvar_node(shell->envvar, "SHLVL");
	if (!node || !node->data)
		return ;
	envv_struct = node->data;
	if (!envv_struct->env_value)
		level = 0;
	else
		level = ft_atoi(envv_struct->env_value);
	level++;
	new_value = ft_itoa(level);
	if (!new_value)
		return ;
	free(envv_struct->env_value);
	envv_struct->env_value = new_value;
}

t_shell	*init_minishell(char **envv)
{
	t_shell	*shell;

	shell = calloc_and_check_alloc(1, sizeof(t_shell), "(init minishell - \
	malloc error");
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	shell->last_exit_status = 0;
	shell->envvar = NULL;
	shell->pids = NULL;
	shell->input = NULL;
	shell->contains_pipe = false;
	shell->num_of_cmds = 0;
	shell->cmd_queue = NULL;
	shell->is_heredoc = false;
	clone_envv_to_dlist(shell, envv);
	increment_shlvl(shell);
	if (set_signal_handling(shell) || set_termios(shell))
	{
		shell->last_exit_status = 1;
		error_and_exit(shell, "Error setting up signal handling or termios");
	}
	return (shell);
}

t_exec_params	init_exec_params(t_shell *shell)
{
	t_exec_params	params;

	params.shell = shell;
	params.cmd = NULL;
	params.pipes = NULL;
	params.num_pipes = 0;
	params.cmd_index = 0;
	params.num_cmds = 0;
	return (params);
}
