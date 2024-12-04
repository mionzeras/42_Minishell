/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:37:01 by caliman           #+#    #+#             */
/*   Updated: 2024/12/03 18:24:55 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env *node, t_env *new)
{
	t_env	*last;

	last = node;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
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
	// delete_list(list);
	return (head);
}

void	print_env_list(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
		{
			ft_putstr_fd(tmp->content, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		tmp = tmp->next;
	}
}

void	ft_env(t_env *env_list, t_organize *program)
{
	if (program->cmds[3])
		ft_error_cmds(program->cmds, 127);
	else if (program->args)
	{
		ft_error_env_dir(program->args, 1);
	}
	else
		print_env_list(env_list);
}
