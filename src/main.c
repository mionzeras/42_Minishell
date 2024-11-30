/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:32:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/30 15:38:46 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_program	mini;
	// int			fd1;
	// int			fd2;
	// fd1 = dup(STDIN);
	// fd2 = dup(STDOUT);
	if (argc != 1 || argv[1] || !env || !*env)
	{
		if (argc != 1 || argv[1])
			ft_printf("Error: No arguments needed\n");
		if (!env || !*env)
			ft_printf("Error: No environment\n");
		return (EXIT_FAILURE);
	}
	signals_loop();
	//init_struct(&mini, env);
	mini.env_list = init_env(env);
	update_sh_lvl(mini.env_list);
	mini_loop(&mini);
	delete_list(mini.env_list);
	// close(fd1);
	// close(fd2);
	return (g_exit_status);
}
