#include "minishell.h"

void	handle_quote(t_shell *shell, const char *input, int *i, int start)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
	create_and_add_token(shell, start, *i);
}

int	handle_no_quote(t_shell *shell, const char *input, int *i, int start)
{
	char	quote;

	while (input[*i] && !ft_isspace(input[*i]) && \
	!is_redirect_or_pipe(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	if (start < *i)
	{
		create_and_add_token(shell, start, *i);
	}
	if (check_redir(shell, input, i) == 1)
		return (1);
	return (0);
}

int	create_token(t_shell *shell, const char *input, int *i, int start)
{
	if (input[*i] == '\'' || input[*i] == '\"')
		handle_quote(shell, input, i, start);
	else
	{
		if (handle_no_quote(shell, input, i, start) == 1)
			return (1);
	}
	return (0);
}

int	separate_tokens(t_shell *shell, const char *input)
{
	int	i;
	int	start;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		start = i;
		if (create_token(shell, input, &i, start) == 1)
			return (1);
	}
	return (0);
}

int	add_tokens_to_list(t_shell *shell)
{
	char	*temp;

	temp = evaluate_envvars(shell->input, shell);
	free(shell->input);
	shell->input = temp;
	if (separate_tokens(shell, shell->input) == 1)
		return (1);
	return (0);
}
