#include "minishell.h"

bool	file_exists(const char *file_name)
{
	struct stat	buffer;

	return (stat(file_name, &buffer) == 0);
}

bool	is_redirect(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") || \
		!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (true);
	else
		return (false);
}

int	get_open_flags(bool is_append)
{
	int	open_flags;

	open_flags = O_CREAT | O_WRONLY;
	if (is_append)
		open_flags |= O_APPEND;
	else
		open_flags |= O_TRUNC;
	return (open_flags);
}

char	*read_heredoc(char *delimiter)
{
	char	*result;
	char	*line;
	char	*temp;

	result = ft_strdup("");
	while (42)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		temp = result;
		result = ft_strjoin(result, line);
		free(temp);
		temp = result;
		result = ft_strjoin(result, "\n");
		free(temp);
		free(line);
	}
	return (result);
}
