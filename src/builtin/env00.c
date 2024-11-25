/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env00.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:37:01 by caliman           #+#    #+#             */
/*   Updated: 2024/11/15 22:28:13 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env *list)
{
	int		i;

	i = 0;
	while (list)
	{
		ft_putstr_fd(list->content, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		list = list->next;
		i++;
	}
}

void	ft_env(t_program *mini, t_organize *program)
{
	if (program->cmds[3])
		ft_error_cmds(program);
	else if (program->args)
		ft_error_args();
	else
	{
		print_env_list(mini->env_list);
	}
}