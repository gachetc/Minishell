#include "minishell.h"

static char	*handle_env_var(char *var_start, t_shell *shell, char **result)
{
	char	*var_end;
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_end = var_start + 1;
	while (ft_isalnum(*var_end) || *var_end == '_')
		var_end++;
	var_name = ft_substr(var_start, 1, var_end - var_start - 1);
	var_value = get_env_value(shell->envvar, var_name);
	free(var_name);
	temp = *result;
	if (var_value != NULL)
		*result = ft_strjoin(*result, var_value);
	else
		*result = ft_strjoin(*result, "");
	free(temp);
	return (var_end);
}

static char	*handle_dollar_or_question(char *var_start, t_shell *shell, \
		char **result)
{
	char	*temp;
	char	*status;

	if (*(var_start + 1) == '\0' || ft_isspace(*(var_start + 1)))
	{
		temp = *result;
		*result = ft_strjoin(*result, "$");
		free(temp);
		return (var_start + 1);
	}
	else if (*(var_start + 1) == '?')
	{
		status = ft_itoa(shell->last_exit_status);
		temp = *result;
		*result = ft_strjoin(*result, status);
		free(temp);
		free(status);
		return (var_start + 2);
	}
	return (NULL);
}

char	*handle_special_vars(char *var_start, t_shell *shell, char **result)
{
	char	*new_var_start;
	int		i;

	i = 0;
	new_var_start = handle_dollar_or_question(var_start, shell, result);
	if (new_var_start)
		return (new_var_start);
	if (var_start[i] == '$' && (var_start[i + 1] \
				== '\"' || var_start[i + 1] == '\''))
	{
		*result = single_dollar_checker(var_start, result);
		return (var_start + 2);
	}
	return (handle_env_var(var_start, shell, result));
}

char	*handle_single_quotes(char *str, char *var_start, char **result)
{
	char	*single_quote_start;
	char	*single_quote_end;
	char	*before_var;
	char	*temp;

	single_quote_start = ft_strrchr(str, '\'');
	if (single_quote_start && single_quote_start < var_start)
	{
		single_quote_end = ft_strchr(single_quote_start + 1, '\'');
		if (single_quote_end && single_quote_end > var_start)
		{
			before_var = ft_substr(str, 0, single_quote_end - str + 1);
			temp = *result;
			*result = ft_strjoin(*result, before_var);
			free(temp);
			free(before_var);
			return (single_quote_end + 1);
		}
	}
	return (NULL);
}

void	handle_no_value(t_shell *shell, int *i, char *key)
{
	int		length;
	char	*temp_str;

	if (ft_strcmp(key, "?") == 0)
	{
		*i += 2;
		free(key);
		return ;
	}
	length = ft_strlen(key);
	temp_str = ft_replace_substr(shell->input, *i, (*i + length + 1), "");
	free(shell->input);
	shell->input = temp_str;
	free(key);
}
