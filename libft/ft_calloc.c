/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:27:18 by gcampos-          #+#    #+#             */
/*   Updated: 2023/04/24 19:23:32 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_len;
	void	*p;

	total_len = nmemb * size;
	p = malloc(total_len);
	if (!p)
		return (NULL);
	ft_memset(p, 0, total_len);
	return (p);
}
