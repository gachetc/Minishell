#include "minishell.h"

static void	swap_adjacent(t_list **head, t_list *node1, t_list *node2)
{
	node1->next = node2->next;
	node2->prev = node1->prev;
	node1->prev = node2;
	node2->next = node1;
	if (node1->next)
		node1->next->prev = node1;
	if (node2->prev)
		node2->prev->next = node2;
	else
		*head = node2;
}

static void	swap_non_adjacent(t_list **head, t_list *node1, t_list *node2)
{
	t_list	*temp_next;
	t_list	*temp_prev;

	(void)head;
	temp_next = node1->next;
	node1->next = node2->next;
	node2->next = temp_next;
	temp_prev = node1->prev;
	node1->prev = node2->prev;
	node2->prev = temp_prev;
	if (node1->next)
		node1->next->prev = node1;
	if (node1->prev)
		node1->prev->next = node1;
	else
		*head = node1;
	if (node2->next)
		node2->next->prev = node2;
	if (node2->prev)
		node2->prev->next = node2;
	else
		*head = node2;
}

void	ft_lstswap_nodes(t_list **head, t_list *node1, t_list *node2)
{
	t_list	*temp;

	if (node1 == node2 || !head || !*head || !node1 || !node2)
		return ;
	if (node1->prev == node2)
	{
		temp = node1;
		node1 = node2;
		node2 = temp;
	}
	if (node1->next == node2)
		swap_adjacent(head, node1, node2);
	else
		swap_non_adjacent(head, node1, node2);
}
