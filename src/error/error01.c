/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:25:27 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/12/04 23:48:35 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_digit(char *str, int status)
{
	ft_printf("minishell: exit: %s: numeric argument required", str);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_path_cmd(char *cmd, int status)
{
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": command not found", STDERR);
	ft_putstr_fd("\n", STDERR);
	g_exit_status = status;
	printf("status: %d\n", g_exit_status);
	return ;
}
void	ft_error_env_dir(char *dir, int status)
{
	ft_putstr_fd("env: '", STDERR);
	ft_putstr_fd(dir, STDERR);
	ft_putstr_fd("': No such file or directory\n", STDERR);
	g_exit_status = status;
	return ;
}

void	ft_error_exp_equal(char *dir, int status)
{
	ft_putstr_fd("minishell: export: `=", STDERR);
	ft_putstr_fd(dir, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	g_exit_status = status;
	return ;
}