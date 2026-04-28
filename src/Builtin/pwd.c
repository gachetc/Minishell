#include "minishell.h"

static void	print_env_value(int fd, t_envv *envv_element)
{
	if (envv_element != NULL && envv_element->env_value != NULL)
	{
		ft_putstr_fd(envv_element->env_value, fd);
		ft_putstr_fd("\n", fd);
	}
}

static void	print_current_working_directory(int fd)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd("Error: Unable to get current working directory\n", fd);
	}
}

int	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	t_list	*pwd_node;

	if (!cmd || !shell->envvar)
		return (1);
	pwd_node = find_envvar_node(shell->envvar, "PWD");
	if (!pwd_node || pwd_node->data == NULL)
	{
		print_current_working_directory(cmd->out_fd);
	}
	else
	{
		print_env_value(cmd->out_fd, (t_envv *)pwd_node->data);
	}
	shell->last_exit_status = 0;
	return (0);
}
