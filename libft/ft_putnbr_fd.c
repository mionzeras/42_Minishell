/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:26:26 by gcampos-          #+#    #+#             */
/*   Updated: 2023/05/02 16:10:14 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	li;

	li = n;
	if (li < 0)
	{
		ft_putchar_fd('-', fd);
		li *= -1;
	}
	if (li > 9)
		ft_putnbr_fd(li / 10, fd);
	ft_putchar_fd(li % 10 + '0', fd);
}
