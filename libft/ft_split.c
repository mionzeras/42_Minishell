/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:06:54 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/16 12:06:06 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//count words in string
int	count_wrd(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			count++;
		}
		i++;
	}
	return (count);
}

//count letters in words
size_t	cliw(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	str_size;
	size_t	wrd_size;
	char	**str_final;

	i = 0;
	if (!s)
		return (NULL);
	str_size = count_wrd(s, c);
	str_final = malloc((str_size + 1) * sizeof(char *));
	if (!str_final)
		return (NULL);
	while (i < str_size)
	{
		while (*s && *s == c)
			s++;
		wrd_size = cliw(s, c);
		str_final[i] = ft_substr(s, 0, wrd_size);
		s = (s + wrd_size) + 1;
		i++;
	}
	str_final[str_size] = NULL;
	return (str_final);
}
