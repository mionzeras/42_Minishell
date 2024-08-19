/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:17:03 by gcampos-          #+#    #+#             */
/*   Updated: 2024/02/27 15:03:42 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	pf_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (pf_putstr("(null)"));
	while (str[i])
	{
		pf_putchar(str[i]);
		i++;
	}
	return (i);
}

int	pf_putnbr(int nb)
{
	char	*str;
	int		i;

	str = ft_itoa(nb);
	i = pf_putstr(str);
	free(str);
	return (i);
}
