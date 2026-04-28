#include "minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	if (!str || !to_find)
		return (NULL);
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] != '\0')
		{
			j++;
		}
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void	free_resources(char *path, char *old_pwd)
{
	if (path && path != NULL)
	{
		free(path);
	}
	if (old_pwd && old_pwd != NULL)
	{
		free(old_pwd);
	}
}

int	free_and_return(char	*path, char	*old_pwd, int return_value)
{
	if (path && path != NULL)
	{
		free(path);
	}
	if (old_pwd && old_pwd != NULL)
	{
		free(old_pwd);
	}
	return (return_value);
}

char	*remove_all_quotes(char *str)
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

char	*get_path_from_args(t_cmd *cmd_struct)
{
	char	*path;
	char	*temp;

	path = get_new_path(cmd_struct);
	if (path)
	{
		temp = path;
		path = remove_all_quotes(path);
		free(temp);
	}
	return (path);
}
