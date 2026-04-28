#include "minishell.h"

char	*process_argument_main(char *arg, t_shell *shell)
{
	char	*result;
	size_t	len;
	size_t	i;
	char	*processed_char;

	i = 0;
	result = ft_strdup("");
	shell->in_single_quote = false;
	shell->in_double_quote = false;
	len = ft_strlen(arg);
	while (i < len)
	{
		processed_char = process_character(arg[i], arg, &i, shell);
		result = ft_strjoin_free(result, processed_char, 1);
		free(processed_char);
		i++;
	}
	return (result);
}

void	process_argument(t_shell *shell, char *arg, char **result)
{
	char	*processed_arg;

	processed_arg = process_argument_main(arg, shell);
	*result = ft_strjoin_free(*result, processed_arg, 1);
	free(processed_arg);
}

void	handle_argument(t_shell *shell, t_list *arg_node, char **result, \
		bool print_newline)
{
	char	*arg;

	arg = (char *)arg_node->data;
	if (ft_strcmp(arg, "-n") != 0 || print_newline)
		process_argument(shell, arg, result);
	add_space(arg_node, result);
}
