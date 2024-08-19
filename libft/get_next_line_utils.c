/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:41:20 by gcampos-          #+#    #+#             */
/*   Updated: 2024/03/14 18:05:16 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_strlen(char *s1)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	return (i);
}

char	*get_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if ((unsigned char)str[i] == (unsigned char)c)
		return (&str[i]);
	return (NULL);
}

char	*get_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*strnew;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	i = get_strlen(s1);
	j = 0;
	strnew = (char *)malloc(sizeof(char) * (i + get_strlen(s2) + 1));
	if (!strnew)
		return (NULL);
	while (s1[j])
	{
		strnew[j] = s1[j];
		j++;
	}
	j = -1;
	while (s2[++j])
		strnew[i + j] = s2[j];
	strnew[i + j] = '\0';
	free(s1);
	return (strnew);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		line = (char *)malloc(sizeof (char) * i + 1);
	else
		line = (char *)malloc(sizeof (char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*keep_rest(char *str)
{
	int		i;
	int		j;
	char	*keep_line;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	keep_line = malloc(sizeof(char) * (get_strlen(str) - i));
	if (!keep_line)
		return (NULL);
	i++;
	while (str[i] && str[i] != '\0')
		keep_line[j++] = str[i++];
	keep_line[j] = '\0';
	free(str);
	return (keep_line);
}
