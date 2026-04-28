#include "minishell.h"

void	concat_before_var(char *str, char *var_start, char **result)
{
	char	*before_var;
	char	*temp;

	if (var_start == str || !var_start || !*result || !str)
		return ;
	before_var = ft_substr(str, 0, var_start - str);
	if (!before_var)
		return ;
	temp = *result;
	*result = ft_strjoin(*result, before_var);
	if (!*result)
	{
		free(before_var);
		return ;
	}
	free(temp);
	free(before_var);
}

void	expand_envvar(t_shell *shell, int *i)
{
	char	*key;
	char	*value;
	int		length;
	char	*temp_str;

	key = get_env_key(shell->input + *i + 1);
	if (!key)
		return ;
	value = get_env_value(shell->envvar, key);
	length = ft_strlen(key);
	if (!value)
		temp_str = ft_replace_substr(shell->input, *i, *i + length + 1, "");
	else
		temp_str = ft_replace_substr(shell->input, *i, *i + length + 1, value);
	free(shell->input);
	shell->input = temp_str;
	if (value)
		*i += ft_strlen(value) - 1;
	else
		*i -= 1;
	free(key);
}

static void	handle_single_quote(char **str, char **result, t_shell *shell)
{
	char	*temp;

	shell->in_single_quote = !shell->in_single_quote;
	temp = ft_strjoin_char(*result, **str);
	free(*result);
	*result = temp;
	(*str)++;
}

static void	handle_double_quote(char **str, char **result, t_shell *shell)
{
	char	*temp;

	shell->in_double_quote = !shell->in_double_quote;
	temp = ft_strjoin_char(*result, **str);
	free(*result);
	*result = temp;
	(*str)++;
}

char	*evaluate_envvars(char *str, t_shell *shell)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	while (*str)
	{
		if (*str == '\'' && !shell->in_double_quote && shell->is_heredoc == 0)
		{
			handle_single_quote(&str, &result, shell);
			continue ;
		}
		if (*str == '\"' && !shell->in_single_quote)
		{
			handle_double_quote(&str, &result, shell);
			continue ;
		}
		if (*str == '$' && (!shell->in_single_quote || shell->is_heredoc == 1))
		{
			handle_envv_var(&str, &result, shell);
			continue ;
		}
		add_char_to_result(&str, &result);
	}
	return (result);
}
