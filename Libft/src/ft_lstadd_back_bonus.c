/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:33:42 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:52:38 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst_head, t_list *new_node)
{
	t_list	*last;

	if (!lst_head || !new_node)
		return ;
	if (!*lst_head)
	{
		*lst_head = new_node;
		return ;
	}
	last = ft_lstlast(*lst_head);
	last->next = new_node;
	new_node->prev = last;
}
