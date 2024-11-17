/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/17 17:42:32 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_loop(t_program *mini)
{
	t_organize	*program;

	program = NULL;
	while (mini->loop == 0)
	{
		if (parseline(mini))
			continue ;
		program = init_organize(mini);
		parse_input(mini, program);
		if (ft_strncmp(mini->user_input, "exit", 4) == 0)
		{
			free_organize(program);
			break ;
		}
		free_organize(program);
		free(mini->user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

