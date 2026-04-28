#include "minishell.h"

void	free_exec_arrays(char **env, char **arg)
{
	if (env)
		free_array((void **)env);
	if (arg)
		free(arg);
}

void	reset_file_descriptors(t_shell *shell)
{
	if (dup2(shell->original_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 reset stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(shell->original_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 reset stdout");
		exit(EXIT_FAILURE);
	}
}

int	**init_pipes(t_exec_params *params)
{
	int		**pipes;
	int		i;

	pipes = malloc(params->num_pipes * sizeof(int *));
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < params->num_pipes)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("malloc/pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes(t_exec_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_pipes)
	{
		close(params->pipes[i][0]);
		close(params->pipes[i][1]);
		free(params->pipes[i]);
		i++;
	}
	free(params->pipes);
}

void	close_pipe(int fd)
{
	if (fd != -1)
		close(fd);
}
