/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/30 13:53:39 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fd_signals(int const fd, int const fd1)
{
	// ft_handle_signals(MAIN);
	dup2(fd, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

int	mini_loop(t_program *mini)
{
	t_organize	*program;
	char		*input;

	while (1)
	{
		program = NULL;
		// reset_fd_signals(fd1, fd2);
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT);
			return (EXIT_SUCCESS);
		}
		if (parse_readline(&input, mini->env_list) == 0)
		{
			program = init_organize(input, mini);
			if (parse_organize(program, input, mini->env_list) == 1)
			{
				free_organize(program);
				free_ptr(input);
				continue ;
			}
			if (mini->pipes > 0)
				executor(program, mini);
			else
				exec_one_cmd(mini, program);
			free_organize(program);
			free_ptr(input);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
