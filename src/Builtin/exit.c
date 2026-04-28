#include "minishell.h"

int	handle_too_many_args(void)
{
	ft_printf("cd: too many arguments\n");
	return (1);
}

static int	is_valid_numeric(const char *arg)
{
	if (arg == NULL || *arg == '\0')
	{
		return (0);
	}
	if (*arg == '+' || *arg == '-')
	{
		arg++;
	}
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9'))
		{
			return (0);
		}
		arg++;
	}
	return (1);
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->arguments)
	{
		if (!is_valid_numeric((char *)cmd->arguments->data))
		{
			shell->last_exit_status = 255;
			error_and_exit(shell, "exit\nnumeric argument required");
		}
		if (cmd->arguments->next != NULL)
		{
			shell->last_exit_status = EXIT_FAILURE;
			error("exit\ntoo many arguments", NULL);
			return (EXIT_FAILURE);
		}
		exit_status = ft_atoi((char *)cmd->arguments->data);
		exit_status = exit_status % 256;
		if (exit_status < 0)
			exit_status += 256;
	}
	shell->last_exit_status = exit_status;
	exit(exit_status);
	return (exit_status);
}
