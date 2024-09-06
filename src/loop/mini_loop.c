/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/06 14:42:04 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int mini_loop(t_program *mini)
{
	while(!mini->stop)
	{
		char *tmp;

		mini->user_input = readline(MINI_MSG);
		if (!mini->user_input)
			exit(EXIT_SUCCESS);
		tmp = ft_strtrim(mini->user_input, " ");
		free(mini->user_input);
		mini->user_input = tmp;
		if (!mini->user_input)
			exit(EXIT_SUCCESS);
		if(ft_strncmp(mini->user_input, "exit", 4) == 0)
			break;
		if (ft_strlen(mini->user_input) > 0)
			add_history(mini->user_input);
		parse_input(mini);
		printf("user_input: %s\n", mini->user_input);
		free(tmp);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
