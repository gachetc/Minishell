/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:40:40 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:51:47 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst_head, t_list *new_node)
{
	if (!new_node)
		return ;
	new_node->next = *lst_head;
	new_node->prev = NULL;
	if (*lst_head)
		(*lst_head)->prev = new_node;
	*lst_head = new_node;
}
