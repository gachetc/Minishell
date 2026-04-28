/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicbachmann <ludovicbachmann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:51:05 by lubachma          #+#    #+#             */
/*   Updated: 2024/08/14 00:50:23 by ludovicbach      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_check(const char format, va_list args)
{
	int	result;

	result = 0;
	if (format == '%')
		result += ft_putchar('%');
	else if (format == 'c')
		result += ft_putchar(va_arg(args, int));
	else if (format == 's')
		result += ft_putstr(va_arg(args, char *));
	else if (format == 'd')
		result += ft_putnbr(va_arg(args, int));
	else if (format == 'p')
		result += ft_putptr(va_arg(args, unsigned long));
	else if (format == 'i')
		result += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		result += ft_putunsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		result += ft_puthex(va_arg(args, unsigned int));
	else if (format == 'X')
		result += ft_puthexx(va_arg(args, unsigned int));
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	res;
	int				i;

	if (!format)
		return (0);
	res = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			res += format_check(format[i], args);
		}
		else
		{
			res += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (res);
}
