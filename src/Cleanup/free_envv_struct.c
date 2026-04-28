#include "minishell.h"

void	free_envv_struct(void *data)
{
	t_envv	*envv;

	envv = (t_envv *)data;
	if (envv)
	{
		if (envv->env_key)
			free(envv->env_key);
		if (envv->env_value)
			free(envv->env_value);
		free(envv);
	}
}
