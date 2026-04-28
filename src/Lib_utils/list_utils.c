#include "minishell.h"

bool	ft_lsthas_node(t_list *lst_head, t_list *node_to_find)
{
	t_list	*curr;

	curr = lst_head;
	while (curr != NULL)
	{
		if (curr == node_to_find)
			return (true);
		curr = curr->next;
	}
	return (false);
}

void	ft_lstdel_head(t_list **lst_head, void (*del)(void*))
{
	t_list	*temp;

	if (!lst_head || !*lst_head)
		return ;
	if (!(*lst_head)->next)
	{
		del((*lst_head)->data);
		free_null((void **)lst_head);
		return ;
	}
	temp = (*lst_head)->next;
	temp->prev = NULL;
	del((*lst_head)->data);
	free_null((void **)lst_head);
	*lst_head = temp;
}

void	ft_lstdel_node(t_list **lst_head, t_list *node_to_del, \
		void (*del)(void*))
{
	if (!lst_head || !*lst_head || !node_to_del || \
			!ft_lsthas_node(*lst_head, node_to_del))
		return ;
	if (node_to_del == *lst_head)
	{
		ft_lstdel_head(lst_head, del);
		return ;
	}
	if (node_to_del->prev)
		node_to_del->prev->next = node_to_del->next;
	if (node_to_del->next)
		node_to_del->next->prev = node_to_del->prev;
	del(node_to_del->data);
	free(node_to_del);
}
