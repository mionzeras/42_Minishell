/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 00:28:48 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_program *mini)
{
	mini->token = malloc(sizeof(t_token));
	if(!mini->token)
	{
		printf("Error: malloc failed\n");
		return ;
	}
	mini->token->cmds = ft_split(mini->user_input, ' ');
	if(!mini->token->cmds)
	{
		printf("Error: split failed\n");
		return ;
	}
}
