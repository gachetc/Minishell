/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:13:08 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:50:39 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptrhex(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_ptrhex(n / 16);
	if (n % 16 < 10)
		count += ft_putchar((n % 16) + '0');
	else
		count += ft_putchar((n % 16) - 10 + 'a');
	return (count);
}

int	ft_putptr(unsigned long n)
{
	int				count;
	unsigned long	*ptr;

	ptr = &n;
	count = 0;
	count += write(1, "0x", 2);
	if (!n)
		return (count += write(1, "0", 1));
	count += ft_ptrhex(*ptr);
	return (count);
}
