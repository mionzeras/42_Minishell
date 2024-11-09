/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/09 17:21:34 by gcampos-         ###   ########.fr       */
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
		tmp = program->next;
		free(program->input_file);
		free(program->output_file);
		free(program->append_file);
		free(program->heredoc_dlm);
		free(program->cmds);
		free(program->args);
		//free(program);
		program = tmp;
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
