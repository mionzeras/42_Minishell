/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:40:54 by caliman           #+#    #+#             */
/*   Updated: 2024/11/14 18:49:44 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
}

void	ft_error_cmds(t_organize *program)
{
	ft_putstr_fd(program->cmds, STDERR);
	ft_putstr_fd(": command not found", STDERR);
	ft_putstr_fd("\n", STDERR);
	return ;
}

void	ft_error_args()
{
	ft_putstr_fd("command 'env' doesn't accept arguments", STDERR);
	ft_putstr_fd("\n", STDERR);
	return ;
}