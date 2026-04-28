#include "minishell.h"

int	check_syntax(char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (1);
	if (equal_sign == str || (equal_sign > str && *(equal_sign - 1) == ' '))
	{
		error("not a valid identifier", equal_sign);
		return (-1);
	}
	return (0);
}
