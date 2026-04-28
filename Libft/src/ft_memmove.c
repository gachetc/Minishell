/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:40:38 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:53:18 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move(char *dst, const char *src, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*char_dst;
	const unsigned char	*char_src;

	char_dst = (unsigned char *)dst;
	char_src = (const unsigned char *)src;
	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if (dst < src || dst >= src + len)
	{
		move(dst, src, len);
	}
	else
	{
		i = len - 1;
		while (len--)
		{
			char_dst[i] = char_src[i];
			--i;
		}
	}
	return (dst);
}

static void	move(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (len--)
	{
		dst[i] = src[i];
		i++;
	}
}
