/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:59:04 by dahkang           #+#    #+#             */
/*   Updated: 2022/10/03 22:54:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_addr(void *ptr)
{
	char				str[20];
	unsigned long long	addr;

	addr = (unsigned long long)ptr;
	if (write(1, "0x", 2) > 0)
	{
		pf_itoa_hex(addr, str, 'x');
		if (write(1, str, ft_strlen(str)) > 0)
			return (ft_strlen(str) + 2);
	}
	return (-1);
}

static int	pf_conversion(const char *format, va_list ap)
{
	if (*format == 'c')
		return (print_char(va_arg(ap, int)));
	else if (*format == 's')
		return (print_str(va_arg(ap, char *)));
	else if (*format == 'p')
		return (print_addr(va_arg(ap, void *)));
	else if (*format == 'd' || *format == 'i')
		return (print_decimal(va_arg(ap, int)));
	else if (*format == 'u')
		return (print_udecimal(va_arg(ap, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (print_hex(va_arg(ap, unsigned int), *format));
	else if (*format == '%')
		return (write(1, "%", 1));
	else
		return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	int		converted_len;
	va_list	ap;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			converted_len = pf_conversion(++format, ap);
			if (converted_len < 0)
				return (-1);
			ret += converted_len;
			format++;
		}
		else
		{
			if (write(1, format++, 1) < 0)
				return (-1);
			ret++;
		}
	}
	va_end(ap);
	return (ret);
}
