/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:12 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**save_path(t_program *mini, char **envp)
{
	t_program	*mini_tmp;
	int		i;
	char	*tmp;

	mini_tmp = mini;
	i = -1;
	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	mini_tmp->path = ft_split(*envp + 5, ':');
	while (mini_tmp->path[++i])
	{
		tmp = ft_strjoin(mini_tmp->path[i], "/");
		free (mini_tmp->path[i]);
		mini_tmp->path[i] = tmp;
	}
	return (mini_tmp->path);
}
void	init_organize(t_input_organize *program)
{
	program->pipes = 0;
	program->input_file = NULL;
	program->output_file = NULL;
	program->append_file = NULL;
	program->heredoc_delimiter = NULL;
	program->cmd_split = NULL;
}

void init_struct(t_program *mini, char **env)
{
	mini->env = env;
	mini->path = save_path(mini, env);
	mini->user_input = NULL;
	mini->pwd = getcwd(0, 0);
	mini->old_pwd = NULL;
	mini->loop = ON;
}
