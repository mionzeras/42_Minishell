/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:48:24 by gcampos-          #+#    #+#             */
/*   Updated: 2024/06/05 18:28:32 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str2;
	int		i;

	str2 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	if (!str2)
		return (NULL);
	while (s[i])
	{
		str2[i] = s[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
