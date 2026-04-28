/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:03:59 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:54:02 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
		len++;
	}
	return (len);
}
