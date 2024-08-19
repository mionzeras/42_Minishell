/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 23:14:42 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_meta_chars(t_program *mini, int i)
{
	if(ft_strncmp(mini->token->cmds[i], "|", 1) == 0)
		mini->token->types[i] = PIPE;
	else if(ft_strncmp(mini->token->cmds[i], "<\0", 2) == 0)
	{
		mini->token->types[i] = LESS;
		mini->redirection->input_file = ft_strdup(mini->token->cmds[i + 1]);
	}
	else if(ft_strncmp(mini->token->cmds[i], "<<", 2) == 0)
	{
		mini->token->types[i] = LESS_LESS;
		mini->redirection->heredoc_delimiter = ft_strdup(mini->token->cmds[i + 1]);
	}
	else if(ft_strncmp(mini->token->cmds[i], ">\0", 2) == 0)
	{
		mini->token->types[i] = GREATER;
		mini->redirection->truncate_file = ft_strdup(mini->token->cmds[i + 1]);
	}
	else if(ft_strncmp(mini->token->cmds[i], ">>", 2) == 0)
	{
		mini->token->types[i] = GREATER_GREATER;
		mini->redirection->append_file = ft_strdup(mini->token->cmds[i + 1]);
	}
	return (0);
}

void	parse_input(t_program *mini)
{
	int i;

	i = -1;
	if(!mini->token)
		mini->token = malloc(sizeof(t_token));
	mini->token->cmds = ft_split(mini->user_input, ' ');
	if(!mini->token->cmds)
		return ;
	while(mini->token->cmds[++i])
	{
		printf("cmds[%d]: %s\n", i, mini->token->cmds[i]);
	}
	i = -1;
	mini->token->types = malloc(sizeof(t_type) * ft_strlen(mini->user_input));
	while(mini->token->cmds[++i])
	{
		if(strchr(META_CHARS, mini->token->cmds[i][0]))
			set_meta_chars(mini, i);
	}
}
