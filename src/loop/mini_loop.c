/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:01:15 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/29 18:27:44 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_program *mini, t_organize *program)
{
	// int	exit_return;

	// exit_return = 0;
	if (ft_strncmp(program->cmds, "unset", 5) == 0)
		ft_unset(mini->env_list, program);
	else if (ft_strncmp(program->cmds, "export", 6) == 0)
		ft_export(mini->env_list, program->args);
	else if (ft_strncmp(program->cmds, "env", 3) == 0)
		ft_env(mini->env_list, program);
	else if (ft_strncmp(program->cmds, "echo", 4) == 0)
		ft_echo(program);
	else if (ft_strncmp(program->cmds, "cd", 2) == 0)
		ft_cd(mini->env_list, program);
	else if (ft_strncmp(program->cmds, "pwd", 3) == 0)
		ft_pwd(program);
	// else if (ft_strncmp(program->cmds, "exit", 4) == 0)
	// {
	// 	exit_return = ft_exit(program, program->args);
	// 	if (exit_return == EXIT_SUCCESS)
	// 	{
	// 		// free_ptr(input);
	// 		return (1);

	// 	}
	// }
	return (0);
}

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
			printf("cmds: %s\n", program->cmds);
			if (ft_strncmp(program->cmds, "exit", 4) == 0)
			{
				free_organize(program);
				free_ptr(input);
				return (EXIT_SUCCESS);
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
