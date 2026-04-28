#include "minishell.h"

t_list	*clone_list(t_list *original)
{
	t_list	*new_list;
	t_list	*new_node;
	void	*envv;

	new_list = NULL;
	while (original != NULL)
	{
		envv = original->data;
		new_node = ft_lstnew(envv);
		if (!new_node)
		{
			error("clone list new node error\n", NULL);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		original = original->next;
	}
	return (new_list);
}

void	sort_list(t_list **head)
{
	t_list	*curr;
	t_envv	*curr_envv;
	t_envv	*next_envv;

	curr = *head;
	while (curr->next != NULL)
	{
		curr_envv = (t_envv *)(curr->data);
		next_envv = (t_envv *)(curr->next->data);
		if (ft_strcmp(curr_envv->env_key, next_envv->env_key) > 0)
		{
			ft_lstswap_nodes(head, curr, curr->next);
			curr = *head;
		}
		else
			curr = curr->next;
	}
}
