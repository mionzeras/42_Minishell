/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/04 16:28:37 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_loop(t_program *mini, t_input_organize *program)
{
	while (mini->loop == ON)
	{
		if (parseline(mini))
			continue ;
		printf("mini->user_input: %s\n", mini->user_input);
		init_organize(program);
		parse_input(mini, program);
		if (ft_strncmp(mini->user_input, "exit", 4) == 0)
			break ;
		free_organize(program);
		free(mini->user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
