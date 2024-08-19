/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 00:14:00 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_loop(t_program *mini)
{
	while(mini->stop == 0)
	{
		mini->user_input = readline(MINI_MSG);	
		if (!mini->user_input)
			break;
		if(ft_strncmp(mini->user_input, "exit", 4) == 0)
			break;
		if (ft_strlen(mini->user_input) > 0)
			add_history(mini->user_input);
		parse_input(mini);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}