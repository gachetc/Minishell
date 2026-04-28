#include "minishell.h"

static void	print_envvar(int fd, t_envv *envv_element)
{
	if (envv_element != NULL)
	{
		ft_putstr_fd(envv_element->env_key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(envv_element->env_value, fd);
		ft_putstr_fd("\n", fd);
	}
}

int	ft_env(t_shell *msh, t_cmd *cmd)
{
	t_list	*current;
	t_envv	*data;

	if (!cmd || !msh->envvar)
		return (1);
	current = msh->envvar;
	while (current)
	{
		if (!current->data)
			return (1);
		data = (t_envv *)current->data;
		if (data->env_value != NULL)
			print_envvar(cmd->out_fd, data);
		current = current->next;
	}
	msh->last_exit_status = 0;
	return (0);
}
