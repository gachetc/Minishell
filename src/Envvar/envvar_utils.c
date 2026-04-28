#include "minishell.h"

char	*get_env_value(t_list *envvar, char *key)
{
	t_list	*node;
	t_envv	*envv_struct;

	if (!envvar || !key)
		return (NULL);
	node = find_envvar_node(envvar, key);
	if (!node || !node->data)
		return (NULL);
	envv_struct = (t_envv *)node->data;
	return (envv_struct->env_value);
}

void	update_node_value(t_list *envvar_node, char *new_value)
{
	t_envv	*envv_struct;

	if (!envvar_node)
		return ;
	envv_struct = (t_envv *)envvar_node->data;
	if (envv_struct->env_value != NULL)
		free(envv_struct->env_value);
	if (new_value != NULL)
	{
		envv_struct->env_value = ft_strdup(new_value);
		if (envv_struct->env_value == NULL)
		{
			error("strdup error", NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		envv_struct->env_value = NULL;
	}
}

char	*get_env_key(char *str)
{
	int		length;

	length = 0;
	if (!str)
		return (NULL);
	if (str[0] == '?')
		return (ft_substr(str, 0, 1));
	while (str[length] && (ft_isalnum(str[length]) || str[length] == '_'))
		length++;
	return (ft_substr(str, 0, length));
}

t_list	*find_envvar_node(t_list *envvar, char *key)
{
	t_list	*current;
	t_envv	*envv_struct;

	if (!envvar || !key)
		return (NULL);
	current = envvar;
	while (current)
	{
		if (!current->data)
			return (NULL);
		envv_struct = (t_envv *)current->data;
		if (envv_struct->env_key == NULL)
			return (NULL);
		if (ft_strcmp(key, envv_struct->env_key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
