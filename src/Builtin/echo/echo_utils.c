#include "minishell.h"

void	handle_n_argument(t_list **arg_node, bool *print_newline)
{
	char	*arg;
	int		i;

	while (*arg_node)
	{
		arg = (char *)(*arg_node)->data;
		if (arg[0] == '-' && arg[1] == 'n')
		{
			i = 2;
			while (arg[i] == 'n')
				i++;
			if (arg[i] == '\0')
			{
				*print_newline = false;
				*arg_node = (*arg_node)->next;
				continue ;
			}
		}
		break ;
	}
}

void	add_space(t_list *arg_node, char **result)
{
	char	*current;
	char	*next;
	bool	current_quoted;
	bool	next_quoted;
	int		i;

	i = 0;
	if (arg_node->next)
	{
		current = (char *)arg_node->data;
		if (ft_strstr(current, "\"\'\"") != NULL || \
				ft_strstr(current, "\'\"\'") != NULL)
			i++;
		next = (char *)arg_node->next->data;
		current_quoted = (current[0] == '\'' && \
				current[ft_strlen(current) - 1] == '\'') || \
				(current[0] == '\"' && current[ft_strlen(current) - 1] == '\"');
		next_quoted = (next[0] == '\'' && next[ft_strlen(next) - 1] == '\'') || \
			(next[0] == '\"' && next[ft_strlen(next) - 1] == '\"');
		if (!(current_quoted && ft_strlen(current) == 2) && \
		!(next_quoted && ft_strlen(next) == 2) && i == 0)
			*result = ft_strjoin_free(*result, " ", 1);
	}
}

char	*single_dollar_checker(char *var_start, char **result)
{
	char	*temp;
	char	*cleaned_result;

	if ((var_start[0] == '$' && (var_start[1] == '\"' || \
					var_start[1] == '\'') && var_start[2] == '\0') \
			|| var_start[2] == '\'' || var_start[2] == '\"')
	{
		temp = ft_strdup("$");
		*result = ft_strjoin(*result, temp);
		free(temp);
	}
	cleaned_result = remove_all_quotes(*result);
	free(*result);
	*result = cleaned_result;
	return (*result);
}
