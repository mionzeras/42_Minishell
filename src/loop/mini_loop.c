/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/20 19:24:50 by gcampos-         ###   ########.fr       */
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
	//char		*input;

	while (mini->loop == 0)
	{
		reset_fd_signals(fd1, fd2);
		program = NULL;
		//input = readline("minishell$ ");
		if (parseline(mini))
			continue ;
		program = init_organize(mini);
		parse_input(mini->user_input, program);
		if (ft_strncmp(mini->user_input, "exit", 4) == 0)
		{
			free_organize(program);
			break ;
		}
		executor(program, mini);
		free_organize(program);
		free(mini->user_input);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

