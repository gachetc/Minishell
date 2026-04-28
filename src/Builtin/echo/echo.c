#include "minishell.h"

bool	initialize_echo(t_shell *shell, t_cmd *cmd, bool *print_newline, \
		char **result)
{
	if (!cmd)
	{
		error_and_exit(shell, "ft_echo missing cmd");
		shell->last_exit_status = 1;
		return (false);
	}
	*print_newline = true;
	*result = ft_strdup("");
	return (true);
}

void	process_arguments(t_shell *shell, t_cmd *cmd, \
		char **result, bool *print_newline)
{
	t_list	*arg_node;

	arg_node = cmd->arguments;
	handle_n_argument(&arg_node, print_newline);
	while (arg_node)
	{
		if (!(*print_newline) && ft_strcmp((char *)arg_node->data, \
					"-n") == 0)
		{
			arg_node = arg_node->next;
			continue ;
		}
		handle_argument(shell, arg_node, result, *print_newline);
		arg_node = arg_node->next;
	}
}

int	ft_echo(t_shell *shell, t_cmd *cmd)
{
	bool	print_newline;
	char	*result;
	int		output_fd;

	if (!initialize_echo(shell, cmd, &print_newline, &result))
		return (1);
	process_arguments(shell, cmd, &result, &print_newline);
	if (cmd->out_fd != -1)
		output_fd = cmd->out_fd;
	else
		output_fd = STDOUT_FILENO;
	ft_putstr_fd(result, output_fd);
	if (print_newline)
		ft_putstr_fd("\n", output_fd);
	shell->last_exit_status = 0;
	free(result);
	return (0);
}
