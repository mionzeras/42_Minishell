/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:19:03 by gcampos-          #+#    #+#             */
/*   Updated: 2024/02/27 15:03:57 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_ptrlen(unsigned long long nb)
{
	int	cont;

	cont = 0;
	while (nb)
	{
		nb /= 16;
		cont++;
	}
	return (cont);
}

int	pf_putptr(unsigned long long nb)
{
	if (nb == 0)
		return (pf_putchar('0'));
	if (nb >= 16)
	{
		pf_putptr(nb / 16);
		pf_putptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			pf_putchar(nb + '0');
		else
			pf_putchar(nb - 10 + 'a');
	}
	return (pf_ptrlen(nb));
}

int	pf_pointer(unsigned long long ptr)
{
	int	cont;

	if (!ptr)
		return (pf_putstr("(nil)"));
	cont = 0;
	cont += pf_putstr("0x");
	cont += pf_putptr(ptr);
	return (cont);
}
