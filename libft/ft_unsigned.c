/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:56:05 by gcampos-          #+#    #+#             */
/*   Updated: 2024/02/27 15:04:37 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*pf_utoa(unsigned int nb)
{
	char			*str;
	unsigned int	tmp;
	int				count;

	tmp = nb;
	count = 0;
	while (tmp > 0)
	{
		tmp /= 10;
		count++;
	}
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (tmp == 0)
		str[0] = '0';
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count] = nb % 10 + '0';
		nb /= 10;
		count--;
	}
	return (str);
}

int	pf_unsigned(unsigned int nb)
{
	char	*str;
	int		i;

	if (nb == 0)
		return (pf_putchar('0'));
	str = pf_utoa(nb);
	i = pf_putstr(str);
	free(str);
	return (i);
}
