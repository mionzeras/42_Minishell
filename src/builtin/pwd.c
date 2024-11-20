/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:39:16 by caliman           #+#    #+#             */
/*   Updated: 2024/11/20 21:38:35 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Print Working Directory: exibe o caminho
completo do diretório de trabalho atual.
*/

void	ft_pwd(t_organize *program)
{
	char *path;

	if (program->args)
	{
		printf("%s\n", ERROR_PWD_ARGUMENTS);
		return ;
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free_ptr(path);
	}
	else
		printf("%s\n", ERROR_PWD_DIRECTORY);
}