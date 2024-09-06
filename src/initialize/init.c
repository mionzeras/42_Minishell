/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/05 13:10:35 by gcampos-         ###   ########.fr       */
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

void init_struct(t_program *mini, char **env)
{
	mini->env = env;
	save_path(mini, env);
	mini->user_input = NULL;
	mini->pwd = getcwd(NULL, 0);
	mini->old_pwd = NULL;
	mini->stop = 0;
	mini->commands = NULL;
}
