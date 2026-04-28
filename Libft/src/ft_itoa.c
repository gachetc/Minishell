/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:43:28 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:51:39 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	if (n == -2147483648)
		return (11);
	if (n < 0)
		return (1 + ft_numlen(-n));
	if (n < 10)
		return (1);
	return (1 + ft_numlen(n / 10));
}

static void	fill_str(char *str, long long n, int *i)
{
	if (n < 0)
	{
		str[(*i)++] = '-';
		fill_str(str, -n, i);
		return ;
	}
	if (n >= 10)
		fill_str(str, n / 10, i);
	str[(*i)++] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	fill_str(str, (long long)n, &i);
	return (str);
}
