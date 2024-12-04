/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/04 21:06:56 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fd_signals(int const fd, int const fd1)
{
	// ft_handle_signals(MAIN);
	dup2(fd, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

int	mini_loop(t_program *mini, int fd1, int fd2)
{
	t_organize	*program;
	char		*input;

	while (1)
	{
		program = NULL;
		reset_fd_signals(fd1, fd2);
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
			free_ptr(input);
			if (mini->pipes > 0)
				exec_with_pipes(mini, program);
			else
				exec_one_cmd(mini, program, fd1, fd2);
			free_organize(program);
			// delete_list(mini->env_list);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
