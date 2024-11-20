/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:38:25 by caliman           #+#    #+#             */
/*   Updated: 2024/11/17 16:56:42 by fgomes-c         ###   ########.fr       */
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

	if (!args[1])
		return (EXIT_SUCCESS);
    if (args[2])
    {
        print_error(ERROR_EXIT_ARGS);
        return (EXIT_FAILURE);
    }
    if (args[1])
    {
        i = 0;
        while (args[1][i])
        {
            if (args[1][0] == '-' || args[1][0] == '+')
                i++;
            if (!ft_isnumber(args[1][i]))
            {
                print_error(ERROR_EXIT_DIGIT);
                return (EXIT_SUCCESS);
            }
            i++;
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
