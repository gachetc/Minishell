#include "minishell.h"

bool	check_unclosed_quotes(char *input)
{
	char	quote;
	bool	in_quotes;
	int		i;

	quote = '\0';
	in_quotes = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (in_quotes && input[i] == quote)
			{
				in_quotes = false;
				quote = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = true;
				quote = input[i];
			}
		}
		i++;
	}
	return (in_quotes);
}

static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*shlvl;
	char	*user;

	shlvl = NULL;
	user = NULL;
	if (shell->envvar)
	{
		shlvl = get_env_value(shell->envvar, "SHLVL");
		user = get_env_value(shell->envvar, "USER");
	}
	if (!shlvl)
		shlvl = "";
	if (!user)
		user = "";
	shell->in_double_quote = false;
	shell->in_single_quote = false;
	prompt = ft_strjoin_any(11, MGNTA, "minishell-3.", MGNTA, \
	shlvl, WHITE, ": ", CYAN, user, MGNTA, "$ ", DEF);
	return (prompt);
}

char	*get_input(t_shell *shell) {
	char *line = NULL;
	char *prompt = NULL;

	shell->contains_pipe = false; // DANS VERSION FINALE A LAISSER TRES IMPORTANT
	shell->contains_echo = false; // A LAISSER TRES IMPORTANT
	shell->contains_export = false;
    if (isatty(fileno(stdin))) {
        prompt = get_prompt(shell);
        line = readline(prompt);
        free(prompt);
    } else {
        line = get_next_line(fileno(stdin));
        if (line) {
            char *trimmed_line = ft_strtrim(line, "\n");
            free(line);
            line = trimmed_line;
        }
    }

    if (!line) {
        free_everything(shell);
        exit(EXIT_SUCCESS);
    }

    if (check_unclosed_quotes(line)) {
        error("minishell: syntax error: unclosed quotes", NULL);
        add_history(line);
        free(line);
        return NULL;
    }

    if (line[0] != '\0') {
        add_history(line);
    } 

    return line;
}

bool	is_just_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}
