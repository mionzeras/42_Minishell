/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/23 11:49:51 by gcampos-         ###   ########.fr       */
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

	while (mini->loop == 0)
	{
		program = NULL;
		reset_fd_signals(fd1, fd2);
		input = readline("minishell$ ");
		if (parse_readline(&input) == 0)
		{
			program = init_organize(input);
			parse_organize(program, input);
			if (ft_strncmp(input, "exit", 4) == 0)
			{
				free_organize(program);
				free_ptr(input);
				break ;
			}
			printf("cmds: %s\n", program->cmds);
			if (ft_strncmp(program->cmds, "unset", 5) == 0)
				ft_unset(mini->env_list, program);
			else if (ft_strncmp(program->cmds, "export", 6) == 0)
				ft_export(mini->env_list, program->args);
			else if (ft_strncmp(program->cmds, "env", 3) == 0)
				ft_env(mini->env_list, program);
			else if (ft_strcmp(program->cmds, "echo") == 0)
				ft_echo(program);
			//executor(program, mini);
			free_organize(program);
			free_ptr(input);
		}
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

