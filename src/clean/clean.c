/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:25:00 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 00:04:33 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void *ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}*/

void free_array(char **array)
{
	int i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
}

void free_redirection(t_redirection redirection)
{
	free(redirection.input_file);
	free(redirection.heredoc_file);
	free(redirection.truncate_file);
	free(redirection.append_file);
	
}

void free_token(t_token *token)
{
	if (token)
	{
		if (token->cmds)
			free_array(token->cmds);
		free(token);
	}
}

void free_program(t_program *mini)
{
	free_redirection(mini->redirection);
	free(mini->user_input);
	free(mini->pwd);
	free(mini->old_pwd);
	free_array(mini->path);
	free_token(mini->token);
}
