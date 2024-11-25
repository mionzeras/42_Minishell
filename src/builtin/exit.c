/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:38:25 by caliman           #+#    #+#             */
/*   Updated: 2024/11/25 18:31:14 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função para verificar se um caractere é um dígito.
static	bool ft_isnumber(char str)
{
	if (!str)
		return (false);
	if (!ft_isdigit(str))
		return (false);
	return (true);
}

void	free_and_exit(t_organize *pgr, int status)
{
	free_organize(pgr);
	exit(status);
}

int	check_exit_args(char **args)
{
	int	i;

	if (!args[0])
		return (EXIT_SUCCESS);
	if (args[1])
	{
		print_error(ERROR_EXIT_ARGS);
		return (EXIT_FAILURE);
	}
	if (args[0])
	{
		i = 0;
		while (args[0][i])
		{
			if (args[0][0] == '-' || args[0][0] == '+')
				i++;
			else
			{
				if (!ft_isnumber(args[0][i]))
				{
					print_error(ERROR_EXIT_DIGIT);
					return (EXIT_SUCCESS);   
				}
				else
					i++;
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_organize *program, char *str)
{
	char	**args;

	if (program->cmds[4])
	{
		ft_error_cmds(program);
		return (EXIT_FAILURE);
	}
	else if (!str)
	{
		free_organize(program);
		return (EXIT_SUCCESS);
	}
	args = ft_new_split(str, ' ');
	if (args[0] && check_exit_args(args) == EXIT_FAILURE)
	{
		free_array(args);
		return (EXIT_FAILURE);
	}
	free_organize(program);
	free_array(args);
	return (EXIT_SUCCESS);
}
