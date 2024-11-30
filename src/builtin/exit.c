/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:38:25 by caliman           #+#    #+#             */
/*   Updated: 2024/11/30 15:41:55 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	arg_is_nbr(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

void	check_exit_args(char **args)
{
	if ((args[0][0] == '-' || args[0][0] == '+'))
	{
		if (args[0][0] == '-' && arg_is_nbr(&args[0][1]))
			g_exit_status = 256 - ft_atoi(&args[0][1]);
		else if (args[0][0] == '+' && arg_is_nbr(&args[0][1]))
			g_exit_status = ft_atoi(&args[0][1]);
		else if (!arg_is_nbr(&args[0][1]))
			ft_error_digit(args[0], 2);
	}
	else
	{
		if (!arg_is_nbr(&args[0][0]))
			ft_error_digit(args[0], 2);
		else
			g_exit_status = ft_atoi(args[0]);
	}
}

void	handle_single_arg_exit(t_organize *program, char **args)
{
	if (arg_is_nbr(args[0]))
		check_exit_args(args);
	else
	{
		ft_putstr_fd("exit\n", STDERR);
		ft_error_digit(args[0], 2);
	}
	free_array(args);
	free_organize(program);
}

int	ft_exit(t_organize *program, char *str)
{
	char	**args;

	if (!str)
	{
		g_exit_status = 0;
		free_organize(program);
		return (EXIT_SUCCESS);
	}
	args = ft_new_split(str, ' ');
	if (arg_is_nbr(args[0]) && args[1])
	{
		handle_exit_error(program, args);
		return (EXIT_FAILURE);
	}
	else if (args[1])
	{
		handle_exit_success_args(program, args);
		return (EXIT_SUCCESS);
	}
	else
	{
		handle_single_arg_exit(program, args);
		return (EXIT_SUCCESS);
	}
}
