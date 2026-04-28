#include "minishell.h"

char	*get_new_path(t_cmd	*cmd_struct)
{
	char	*path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cmd_struct->arguments || \
			ft_strcmp(cmd_struct->arguments->data, "~") == 0)
		path = NULL;
	else if (ft_strcmp(cmd_struct->arguments->data, ".") == 0)
		path = ft_strdup(cwd);
	else if (ft_strcmp(cmd_struct->arguments->data, "..") == 0)
		path = ft_strdup("..");
	else
		path = ft_strdup(cmd_struct->arguments->data);
	free(cwd);
	return (path);
}

static void	update_env_vars(t_shell	*shell, char	*old_pwd, char	*new_pwd)
{
	t_list	*current;
	t_envv	*env_var;

	if (!shell->envvar || !old_pwd || !new_pwd)
		return ;
	current = shell->envvar;
	if (!current)
		return ;
	while (current)
	{
		if (!current->data)
			return ;
		env_var = (t_envv *)current->data;
		if (!env_var)
			return ;
		if (ft_strcmp(env_var->env_key, "PWD") == 0)
		{
			free(env_var->env_value);
			env_var->env_value = ft_strdup(new_pwd);
		}
		current = current->next;
	}
	if (!shell->envvar)
		return ;
	update_node_value(find_envvar_node(shell->envvar, "OLDPWD"), old_pwd);
}

static int	change_directory_and_update_env(t_shell *shell, char *path)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;

	if (path && access(path, F_OK) != 0)
	{
		error("No such file or directory", path);
		shell->last_exit_status = 127;
		return (free_and_return(path, NULL, 1));
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (free_and_return(path, NULL, 1));
	if (chdir(path) != 0)
		return (free_and_return(path, old_pwd, 1));
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (!new_pwd)
		return (free_and_return(path, old_pwd, 1));
	update_env_vars(shell, old_pwd, new_pwd);
	free_resources(path, old_pwd);
	return (0);
}

int	ft_cd(t_shell *shell, t_cmd *cmd_struct)
{
	char	*path;
	char	*home;

	if (cmd_struct->arguments && cmd_struct->arguments->next != NULL)
		return (handle_too_many_args());
	path = get_path_from_args(cmd_struct);
	if (!path)
	{
		home = get_env_value(shell->envvar, "HOME");
		if (!home)
		{
			error("cd: HOME not set", NULL);
			shell->last_exit_status = 1;
			return (1);
		}
		path = ft_strdup(home);
	}
	return (change_directory_and_update_env(shell, path));
}
