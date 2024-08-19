/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 14:23:31 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_struct(t_program *mini, char **env)
{
	mini->env = env;
	mini->user_input = NULL;
	mini->pwd = getcwd(NULL, 0);
	mini->old_pwd = NULL;
	save_path(mini, env);
	mini->stop = 0;
	mini->stdin_copy = dup(STDIN);
	mini->stdout_copy = dup(STDOUT);
	mini->redirection = NULL;
	mini->token = NULL;
	//mini->redirection = malloc(sizeof(t_redirection));
	/*if (mini->redirection)
	{
		mini->redirection->input_file = NULL;
		mini->redirection->heredoc_delimiter = NULL;
		mini->redirection->truncate_file = NULL;
		mini->redirection->append_file = NULL;
	}
	mini->token = malloc(sizeof(t_token));
	if (mini->token)
	{
		mini->token->cmds = NULL;
		mini->token->types = NULL;
	}*/
}
