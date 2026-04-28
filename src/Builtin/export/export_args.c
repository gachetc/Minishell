#include "minishell.h"

static int	process_single_export_arg(t_shell *shell, char *arg)
{
	char	*arg_concat;
	char	**str_array;
	int		syntax_check;

	arg_concat = ft_strdup(arg);
	if (!arg_concat)
		return (1);
	if (!ft_strchr(arg_concat, '='))
		return (handle_no_equal_sign(shell, arg_concat));
	syntax_check = check_syntax(arg_concat);
	if (handle_syntax_check(shell, arg_concat, syntax_check))
		return (1);
	str_array = split_arg_export(arg_concat, shell);
	if (handle_str_array(shell, str_array, arg_concat))
		return (1);
	return (handle_str_array_removal(arg_concat, str_array, shell));
}

int	export_args(t_shell *shell, t_cmd *cmd_struct)
{
	t_list	*args;
	int		status;

	args = cmd_struct->arguments;
	status = 0;
	while (args)
	{
		if (process_single_export_arg(shell, (char *)args->data))
			status = 1;
		args = args->next;
	}
	return (status);
}
