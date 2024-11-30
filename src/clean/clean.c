/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/30 15:44:56 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_env *node)
{
	if (node->content)
	{
		free(node->content);
		node->content = NULL;
	}
	if (node)
	{
		free(node);
		node = NULL;
	}
}

void	delete_list(t_env *list)
{
	t_env	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next;
		delete_node(list);
		list = tmp;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_program(t_program *mini)
{
	t_program	*tmp;

	tmp = mini;
	if (tmp->env_list)
		delete_list(tmp->env_list);
	if (tmp)
		free(tmp);
}

void	free_organize(t_organize *program)
{
	t_organize	*tmp;

	while (program)
	{
		tmp = program;
		program = program->next;
		// if (tmp->input_file)
		// 	free_ptr(tmp->input_file);
		// if (tmp->output_file)
		// 	free_ptr(tmp->output_file);
		// if (tmp->append_file)
		// 	free_ptr(tmp->append_file);
		// if (tmp->heredoc_dlm)
		// 	free_ptr(tmp->heredoc_dlm);
		if (tmp->cmds)
			free_ptr(tmp->cmds);
		if (tmp->args)
			free_ptr(tmp->args);
		if (tmp)
			free(tmp);
	}
}
