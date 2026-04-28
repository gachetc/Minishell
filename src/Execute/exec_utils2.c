#include "minishell.h"

void	get_pid_exit_status(t_shell *shell, t_list **pids)
{
	pid_t	*pid;
	int		exit_status;

	while (*pids)
	{
		pid = (pid_t *)(*pids)->data;
		if (*pid > 0)
		{
			waitpid(*pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				shell->last_exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				shell->last_exit_status = 128 + WTERMSIG(exit_status);
			ft_lstdel_head(pids, free_data);
		}
		else
			break ;
	}
}

void	check_command_access(char *path, t_shell *shell)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		error("No such file or directory", path);
		free(path);
		shell->last_exit_status = 127;
		exit(127);
	}
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		error("Is a directory", path);
		free(path);
		shell->last_exit_status = 126;
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		error("Permission denied", path);
		free(path);
		shell->last_exit_status = 126;
		exit(126);
	}
}

void	handle_bin_paths(char **args, t_shell *shell, t_exec_params *params)
{
	int	i;

	i = 1;
	if (ft_strcmp(args[0], "/bin/echo") == 0 && args[1] && \
			ft_strcmp(args[1], "-n") != 0)
	{
		ft_echo(shell, params->cmd);
		exit(shell->last_exit_status);
	}
	else
	{
		while (args[i])
		{
			args[i] = process_argument_main(args[i], shell);
			i++;
		}
	}
}
