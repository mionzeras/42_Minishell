/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:35:08 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/30 15:43:26 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_env *list, char *var)
{
	t_env	*node;
	t_env	*tmp;

	node = list;
	while (node)
	{
		if (ft_strncmp(node->content, var, ft_strlen(var)) == 0)
		{
			if (node->prev)
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			tmp = node->next;
			delete_node(node);
			node = tmp;
		}
		else
			node = node->next;
	}
}

void	ft_unset(t_env *env_list, t_organize *program)
{
	int		i;
	char	**cmd_args;

	if (!program->args)
		return ;
	else
	{
		cmd_args = ft_split(program->args, ' ');
		i = 0;
		while (cmd_args[i])
		{
			remove_env_var(env_list, cmd_args[i]);
			i++;
		}
		if (cmd_args)
		{
			free_array(cmd_args);
			cmd_args = NULL;
		}
	}
}
