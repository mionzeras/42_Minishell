/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 00:23:16 by gcampos-         ###   ########.fr       */
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
}

void init_redirection(t_redirection *redirection)
{
	redirection->input_file = NULL;
	redirection->heredoc_file = NULL;
	redirection->truncate_file = NULL;
	redirection->append_file = NULL;
}

void init_token(t_token *token)
{
	t_token *tmp;
	
	tmp = token;
	tmp = malloc(sizeof(t_token));
	tmp->cmds = NULL;
	tmp->next = NULL;
	tmp->types = NULL;
	free(tmp);
}

int init_program(t_program *mini, char **env)
{
	init_struct(mini, env);
	init_redirection(&mini->redirection);
	init_token(mini->token);
	return (0);
}