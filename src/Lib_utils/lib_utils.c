#include "minishell.h"

char	*ft_replace_substr(char *str, int start, int end, char *substr)
{
	char	*pre_substr;
	char	*post_substr;
	char	*new_str;

	if (!str || !substr)
		return (NULL);
	pre_substr = ft_substr(str, 0, start);
	post_substr = ft_substr(str, end, (ft_strlen(str) - end));
	new_str = ft_strjoin_any(3, pre_substr, substr, post_substr);
	free(pre_substr);
	free(post_substr);
	return (new_str);
}

char	*ft_strjoin_any(int num_of_str, ...)
{
	va_list		args;
	const char	*str;
	char		*result;
	char		*temp;

	if (num_of_str <= 0)
		return (NULL);
	va_start(args, num_of_str);
	result = ft_strdup("");
	while (num_of_str--)
	{
		str = va_arg(args, const char *);
		if (str)
		{
			temp = ft_strjoin(result, str);
			free(result);
			result = temp;
		}
	}
	va_end(args);
	return (result);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

bool	ft_isspace(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (true);
	else
		return (false);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
