/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:39:16 by caliman           #+#    #+#             */
/*   Updated: 2024/11/30 15:43:03 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Print Working Directory: exibe o caminho
completo do diretório de trabalho atual.
*/

void	ft_pwd(t_organize *program)
{
	char	*path;

	if (program->args)
	{
		if (program->args[0] == '-')
		{
			ft_error_args(program->args, 127);
			return ;
		}
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free_ptr(path);
		g_exit_status = 0;
	}
	else
		print_error(ERROR_PWD_DIRECTORY, 1);
}
