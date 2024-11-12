/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:49:09 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/12 20:33:52 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//count words in string
int	count_world(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (inside_quotes(s, i) != 0)
		{
			count++;
			while (inside_quotes(s, i) != 0 && s[i] != '\0')
				i++;
		}
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			count++;
			while (s[i] != '\0' && s[i] != c && inside_quotes(s, i) == 0)
				i++;
		}
		else
			i++;
	}
	return (count);
}

//count letters in words
size_t	countliw(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (inside_quotes(str, i) != 0)
		{
			i++;
			while (inside_quotes(str, i) != 0)
				i++;
		}
		else
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
