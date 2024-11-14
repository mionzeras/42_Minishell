/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:49:09 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/14 19:45:52 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//count words in string
size_t	count_world(char *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] != c && ((i == 0) || s[i - 1] == c))
			count++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;

	}
	return (count);
}

//count letters in words
size_t	countliw(char *str, char c)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

char	**ft_new_split(char *s, char c)
{
	size_t	i;
	size_t	str_size;
	size_t	wrd_size;
	char	**str_final;

	i = 0;
	if (!s)
		return (NULL);
	str_size = count_world(s, c);
	str_final = malloc((str_size + 1) * sizeof(char *));
	if (!str_final)
		return (NULL);
	while (i < str_size)
	{
		while (*s && *s == c)
			s++;
		wrd_size = countliw(s, c);
		str_final[i] = ft_substr(s, 0, wrd_size);
		s += wrd_size;
		while (*s && *s == c)
			s++;
		i++;
	}
	str_final[str_size] = NULL;
	return (str_final);
}
