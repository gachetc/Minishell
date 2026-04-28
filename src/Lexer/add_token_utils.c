#include "minishell.h"

char	*copy_without_quotes(char *str, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != '\0' && str[i] == quote)
			quote = '\0';
		else
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*result;

	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result = copy_without_quotes(str, result);
	return (result);
}

void	create_and_add_token(t_shell *shell, int start, int end)
{
	char	*token_str;
	t_list	*new_node;

	token_str = ft_substr(shell->input, start, end - start);
	if (!token_str)
		error("token_str malloc error", NULL);
	new_node = safe_new_token_node(shell, token_str);
	ft_lstadd_back(&(shell->tokens), new_node);
}

void	tokenise_arg(t_shell *shell, const char *input, int *i)
{
	int	start;
	int	end;

	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (is_valid_arg_char(input[*i]))
	{
		start = *i;
		while (input[*i] && is_valid_arg_char(input[*i]))
		{
			(*i)++;
		}
		end = *i;
		create_and_add_token(shell, start, end);
	}
}

t_list	*safe_new_token_node(t_shell *shell, char *str)
{
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
	{
		ft_lstclear(&shell->tokens, free_data);
		error_exit("safe_new_token_node_error");
	}
	return (new_node);
}
