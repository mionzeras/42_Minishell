/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:38:37 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/05 12:59:21 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *ft_newnode(char *str, t_type token)
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
}

void	*ft_realloc(void *ptr, size_t size)
{
	void *new;

	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
