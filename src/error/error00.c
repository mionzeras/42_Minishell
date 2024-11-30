/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:40:54 by caliman           #+#    #+#             */
/*   Updated: 2024/11/30 11:51:59 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, int status)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_cmds(char *cmds, int status)
{
	ft_putstr_fd(cmds, STDERR);
	ft_putstr_fd(": command not found", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_dir(char *dir, int status)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	ft_putstr_fd(dir, STDERR);
	ft_putstr_fd(": No such file or directory\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_args(char *str, int status)
{
	ft_printf("minishell: %s: invalid argument", str);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_opt(char *str, int status)
{
	ft_printf("minishell: cd: %s: invalid option", str);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	return ;
}
