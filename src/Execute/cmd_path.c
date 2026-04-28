#include "minishell.h"

bool	has_path(char *str)
{
	if (ft_strchr(str, '/') != NULL && (str[0] == '/' || str[0] == '.'))
		return (true);
	return (false);
}

static char	**split_path(t_shell *shell)
{
	char	*path_value;
	char	**path_array;
	int		i;
	int		len;
	char	*new_path;

	path_value = get_env_value(shell->envvar, "PATH");
	if (!path_value)
		return (NULL);
	path_array = ft_split(path_value, ':');
	if (!path_array)
		error_and_exit(shell, "split_path array error");
	i = 0;
	while (path_array[i])
	{
		len = ft_strlen(path_array[i]);
		if (len == 0 || path_array[i][len - 1] != '/')
		{
			new_path = ft_strjoin(path_array[i], "/");
			free(path_array[i]);
			path_array[i] = new_path;
		}
		i++;
	}
	return (path_array);
}

char	*get_path(t_shell *shell, char *command)
{
	char	**path_array;
	char	*absolute_path;
	int		i;

	path_array = split_path(shell);
	if (!path_array)
		return (NULL);
	i = 0;
	while (path_array[i])
	{
		absolute_path = ft_strjoin(path_array[i], command);
		if (!absolute_path)
		{
			shell->last_exit_status = 1;
			error_and_exit(shell, "get_path strjoin error");
		}
		if (access(absolute_path, X_OK) == 0)
		{
			free_array((void **)path_array);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	free_array((void **)path_array);
	return (NULL);
}
