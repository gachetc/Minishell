#include "minishell.h"

void	error_exit(const char *errors)
{
	error(errors, NULL);
	exit(EXIT_FAILURE);
}

void	error(const char *error, char *arg)
{
	ft_putstr_fd(RED"minishell: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(RED": ", STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
	ft_putstr_fd("\n"DEF, STDERR_FILENO);
}

void	free_null(void **mem_ptr)
{
	if (mem_ptr != NULL && *mem_ptr != NULL)
	{
		free(*mem_ptr);
		*mem_ptr = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (result);
}
