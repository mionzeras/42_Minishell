/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:55:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/26 18:50:49 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT, "\n", 1);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	signals_loop(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	g_exit_status = 128 + signum;
}

void	signals_child(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
}

