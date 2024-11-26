/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:55:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/26 17:18:08 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_loop(int signum)
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
	signal(SIGINT, signal_handler_loop);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_child(int signum)
{
	if (signum == SIGQUIT)
	{
		write(STDOUT, "Quit: 3\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT, "\n", 1);
		g_exit_status = 1;
	}
}
