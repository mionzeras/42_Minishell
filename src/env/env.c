/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:51 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/20 22:00:35 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_env *node)
{
	free(node->content);
	free(node);
}

// void	print_env_list(t_env *list)
// {
// 	int		i;

// 	i = 0;
// 	while (list)
// 	{
// 		printf("Node %d:\n", i);
// 		printf("Node address: %p\n", (void *)list);
// 		printf("content: %s\n", list->content);
// 		printf("next: %p\n", (void *)list->next);
// 		printf("prev: %p\n", (void *)list->prev);
// 		list = list->next;
// 		i++;
// 	}
// }

void	add_env_node(t_env *node, t_env *new)
{
	t_env	*last;

	last = node;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	// if(!ft_strcmp(last->content, "PATH")   /// isso e para apagar um node do ''''unset''''
	// 	list->prev->next = list->next;
	// 	free(list->content);
	// 	free(list);
}

t_env	*new_env_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*init_env(char **env)
{
	int		i;
	int		env_size;
	t_env	*list;
	t_env	*head;

	i = -1;
	env_size = 0;
	while (env[++i])
		env_size++;
	i = -1;
	while (++i < env_size)
	{
		if (i == 0)
			list = new_env_node();
		else
			add_env_node(list, new_env_node());
	}
	i = -1;
	head = list;
	while (env[++i])
	{
		list->content = ft_strdup(env[i]);
		list = list->next;
	}
	return (head);
}
