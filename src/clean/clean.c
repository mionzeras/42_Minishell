/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/09 14:37:11 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
}

void	free_organize(t_organize *program)
{
	t_organize	*tmp;

	while (program)
	{
		tmp = program;
		program = program->next;
		free(tmp->input_file);
		free(tmp->output_file);
		free(tmp->append_file);
		free(tmp->heredoc_del);
		free(tmp->cmds);
		free(tmp->args);
		//free(tmp);
	}
}

void	free_program(t_program *mini, t_organize *program)
{
	free_array(mini->path);
	free(mini->pwd);
	free(mini->old_pwd);
	if (mini->user_input)
		free(mini->user_input);
	free_organize(program);
}
