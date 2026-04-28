#include "minishell.h"

int	main(int argc, char **argv, char **envv)
{
	t_shell			*shell;
	t_exec_params	params;

	(void)argv;
	if (argc != 1)
		error_exit("Incorrect number of arguments");
	shell = init_minishell(envv);
	params = init_exec_params(shell);
	while (42)
	{
		shell->input = get_input(shell);
		if (!shell->input)
			continue ;
		if (ft_strcmp(shell->input, "") == 0 || \
			is_just_whitespace(shell->input))
		{
			free(shell->input);
			shell->input = NULL;
			continue ;
		}
		process_input(shell);
		execute_pipeline(shell, params);
		shell->num_of_cmds = 0;
		free_input(shell);
	}
	return (0);
}
