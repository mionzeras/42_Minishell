/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/15 20:02:48 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
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

void	free_organize(t_organize *program)
{
	t_organize	*tmp;

	while (program)
	{
		tmp = program;
		program = program->next;
		if (tmp->input_file)
			free(tmp->input_file);
		if (tmp->output_file)
			free(tmp->output_file);
		if (tmp->append_file)
			free(tmp->append_file);
		if (tmp->heredoc_dlm)
			free(tmp->heredoc_dlm);
		if (tmp->cmds)
			free(tmp->cmds);
		if (tmp->args)
			free(tmp->args);
		if (tmp)
			free(tmp);
	}
}

void	free_program(t_program *mini)  
{
	free_array(mini->path);
	// free_array(mini->env);
	// free_array(mini->export);
	free(mini->pwd);
	free(mini->old_pwd);
	delete_list(mini->env_list);
	delete_list(mini->export_list);
	if (mini->user_input)
		free(mini->user_input);
	if (mini)
		free(mini);
}
