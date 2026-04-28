#include "minishell.h"

bool	cmd_is_builtin(char *command)
{
	const char	*builtins[8];
	int			i;

	builtins[0] = "env";
	builtins[1] = "pwd";
	builtins[2] = "export";
	builtins[3] = "echo";
	builtins[4] = "exit";
	builtins[5] = "cd";
	builtins[6] = "unset";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(command, (char *)builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
