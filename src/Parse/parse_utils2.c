#include "minishell.h"

void	copy_until_quote(const char *cmd, int *i, int *j, t_shell *shell)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"')
		{
			shell->first_quote = cmd[*i];
			(*i)++;
			break ;
		}
		shell->no_quote[(*j)++] = cmd[*i];
		(*i)++;
	}
}

void	copy_after_quote(const char *cmd, int *i, int *j, t_shell *shell)
{
	while (cmd[*i])
	{
		if (cmd[*i] == shell->first_quote)
		{
			(*i)++;
			shell->first_quote = '\0';
			continue ;
		}
		shell->no_quote[(*j)++] = cmd[*i];
		(*i)++;
	}
}
