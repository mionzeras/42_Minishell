/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:03:16 by gcampos-          #+#    #+#             */
/*   Updated: 2024/02/27 15:03:48 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_hexlen(unsigned int nb)
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

int	pf_puthex(unsigned int nb, const char fs)
{
	if (nb == 0)
		return (pf_putchar('0'));
	if (nb >= 16)
	{
		pf_puthex(nb / 16, fs);
		pf_puthex(nb % 16, fs);
	}
	else
	{
		if (nb <= 9)
			pf_putchar(nb + '0');
		else
		{
			if (fs == 'x')
				pf_putchar(nb - 10 + 'a');
			else
				pf_putchar(nb - 10 + 'A');
		}
	}
	return (pf_hexlen(nb));
}
