/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/09 20:34:24 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_loop(t_program *mini, t_input_organize *program)
{
	while(mini->loop == ON)
	{
		parseline(mini);
		init_organize(program);
		parse_input(mini, program);
		/*printf("input_file: %s\n", program->input_file);
		printf("output_file: %s\n", program->output_file);
		printf("append_file: %s\n", program->append_file);
		printf("heredoc_delimiter: %s\n", program->heredoc_delimiter);
		printf("cmds: %s\n", program->cmds);*/
		if(ft_strncmp(mini->user_input, "exit", 4) == 0)
			break;
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
