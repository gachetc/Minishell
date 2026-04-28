#include "minishell.h"

static char	**initialize_str_array(char *str, int index)
{
	char	**str_array;

	str_array = malloc(sizeof(char *) * 3);
	if (!str_array)
		return (NULL);
	str_array[0] = ft_substr(str, 0, index);
	if (!str_array[0])
	{
		free(str_array);
		return (NULL);
	}
	return (str_array);
}

static char	*handle_quotes_export(char *value_start, t_shell *shell)
{
	char	quote;
	char	*quote_end;
	char	*result;

	quote = *value_start;
	value_start++;
	quote_end = ft_strrchr(value_start, quote);
	if (quote_end)
		result = ft_substr(value_start, 0, quote_end - value_start);
	else
		result = ft_strdup(value_start);
	if (!result)
		return (NULL);
	if (quote == '"')
	{
		char *expanded = evaluate_envvars(result, shell);
		free(result);
		return (expanded);
	}
	return (result);
}

static char	*handle_no_quotes(char *value_start, t_shell *shell)
{
	char	*first_space;
	char	*result;

	first_space = ft_strchr(value_start, ' ');
	if (first_space)
		result = ft_substr(value_start, 0, first_space - value_start);
	else
		result = ft_strdup(value_start);
	if (!result)
		return (NULL);
	{
		char *expanded = evaluate_envvars(result, shell);
		free(result);
		return (expanded);
	}
}

static char	**handle_equal_sign(char *str, char *equal_sign, t_shell *shell)
{
	char	**str_array;
	int		index;
	char	*value_start;

	index = equal_sign - str;
	str_array = initialize_str_array(str, index);
	if (!str_array)
		return (NULL);
	value_start = equal_sign + 1;
	if (*value_start == '"' || *value_start == '\'')
		str_array[1] = handle_quotes_export(value_start, shell);
	else
		str_array[1] = handle_no_quotes(value_start, shell);
	if (!str_array[1])
	{
		free(str_array[0]);
		free(str_array);
		return (NULL);
	}
	str_array[2] = NULL;
	return (str_array);
}

char	**split_arg_export(char *str, t_shell *shell)
{
	char	*equal_sign;
	char	**str_array;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		str_array = handle_equal_sign(str, equal_sign, shell);
	else
		str_array = ft_split(str, ' ');
	return (str_array);
}
