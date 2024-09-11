/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:38:37 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/11 19:03:46 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*t_command *ft_newnode(char *str, t_type token)
{
	t_command *new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->cmd = str;
	new->expansion = NULL;
	new->args = NULL;
	new->token = token;
	new->next = NULL;
	return (new);
}*/

void *ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return NULL;
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, original_size);
		free(ptr);
	}
	return new_ptr;
}
