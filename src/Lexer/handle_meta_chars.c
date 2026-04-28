#include "minishell.h"

void	check_state(char current_char, int *state)
{
	if (*state == 0)
	{
		if (current_char == '\'')
			*state = 1;
		else if (current_char == '\"')
			*state = 2;
	}
	else if (*state == 1 && current_char == '\'')
		*state = 0;
	else if (*state == 2 && current_char == '\"')
		*state = 0;
}

int	parse_redirection(t_shell *shell, const char *input, int *i)
{
	int	j;

	j = *i;
	if (input[*i + 1] && input[*i + 2] == input[*i] && input[*i] != '|')
	{
		while (input[*i] && (input[*i] == input[j]))
		{
			(*i)++;
			j++;
		}
		error("syntax error near unexpected token", NULL);
		return (1);
	}
	if (input[*i] == input[*i + 1])
	{
		create_and_add_token(shell, *i, *i + 2);
		*i += 2;
	}
	else
	{
		create_and_add_token(shell, *i, *i + 1);
		(*i)++;
	}
	return (0);
}

int	check_redir(t_shell *shell, const char *input, int *i)
{
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		return (parse_redirection(shell, input, i));
	}
	return (0);
}

bool	is_valid_arg_char(char c)
{
	char	*invalid_chars;

	invalid_chars = "<>|\'\"";
	if (ft_strchr(invalid_chars, c))
		return (false);
	else if (!ft_isprint(c) || ft_isspace(c))
		return (false);
	else
		return (true);
}

bool	is_redirect_or_pipe(char c)
{
	char	*invalid_chars;

	invalid_chars = "<>|";
	if (ft_strchr(invalid_chars, c))
		return (true);
	else
		return (false);
}
