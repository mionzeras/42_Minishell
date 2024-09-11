/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:48:24 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/10 20:38:39 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*copy;
	size_t		len;

	
	len = ft_strlen(str) + 1;
	copy = malloc(len);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, str, len);
	return (copy);
}
