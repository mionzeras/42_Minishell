/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:55:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/13 17:17:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        rl_replace_line("", 0);
        write(STDOUT, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}

void	signal_handler2(int signum)
{
    if (signum == SIGQUIT)
    {
        write(STDOUT, "Quit: 3\n", 8);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
