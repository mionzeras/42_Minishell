/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:19:53 by gcampos-          #+#    #+#             */
/*   Updated: 2024/02/27 15:04:04 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_func(va_list arg, const char fs)
{
	int	len;

	len = 0;
	if (fs == 'c')
		len += pf_putchar(va_arg(arg, int));
	else if (fs == 's')
		len += pf_putstr(va_arg(arg, char *));
	else if (fs == 'p')
		len += pf_pointer(va_arg(arg, unsigned long long));
	else if (fs == 'd' || fs == 'i')
		len += pf_putnbr(va_arg(arg, int));
	else if (fs == 'u')
		len += pf_unsigned(va_arg(arg, unsigned int));
	else if (fs == 'x' || fs == 'X')
		len += pf_puthex(va_arg(arg, unsigned int), fs);
	else if (fs == '%')
		len += pf_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += print_func(arg, str[i]);
		}
		else
			len += pf_putchar(str[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
