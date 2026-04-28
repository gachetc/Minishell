#include "minishell.h"

void	handle_envv_var(char **str, char **result, t_shell *shell)
{
	char	*var_start;
	char	*new_str;

	var_start = *str;
	new_str = handle_single_quotes(*str, var_start, result);
	if (new_str)
	{
		*str = new_str;
		return ;
	}
	concat_before_var(*str, var_start, result);
	var_start = handle_special_vars(var_start, shell, result);
	*str = var_start;
}

void	add_char_to_result(char **str, char **result)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin_char(*result, **str);
	free(temp);
	(*str)++;
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		len;

	if (!str || !c)
		return (NULL);
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
