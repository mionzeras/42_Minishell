/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/08 16:47:52 by gcampos-         ###   ########.fr       */
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
	if (program->input_file)
		free(program->input_file);
	if (program->output_file)
		free(program->output_file);
	if (program->append_file)
		free(program->append_file);
	if (program->heredoc_del)
		free(program->heredoc_del);
	if (program->cmd_split)
		free(program->cmd_split);
	if (program->args)
		free(program->args);
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
