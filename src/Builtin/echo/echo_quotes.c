#include "minishell.h"

void	handle_quotes(char c, t_shell *shell)
{
	if (c == '\'' && !shell->in_double_quote)
		shell->in_single_quote = !shell->in_single_quote;
	else if (c == '\"' && !shell->in_single_quote)
		shell->in_double_quote = !shell->in_double_quote;
}

char	*process_character(char c, char *arg, size_t *i, t_shell *shell)
{
	char	*result;
	char	str[2];

	(void)arg;
	(void)i;
	result = ft_strdup("");
	if ((c == '\'' && !shell->in_double_quote) || (c == '\"' && \
				!shell->in_single_quote))
		handle_quotes(c, shell);
	else
	{
		str[0] = c;
		str[1] = '\0';
		result = ft_strjoin_free(result, str, 1);
	}
	return (result);
}
