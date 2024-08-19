/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:38:37 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 14:26:06 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*save_path(t_program *mini, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	mini->path = ft_split(*envp + 5, ':');
	while (mini->path[++i])
	{
		tmp = ft_strjoin(mini->path[i], "/");
		free (mini->path[i]);
		mini->path[i] = tmp;
	}
	return (EXIT_SUCCESS);
}


