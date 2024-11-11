/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/11 19:44:20 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_args(char *dest, char *src)
{
	char	*tmp;
	
	if (!dest)
		return (ft_strdup(src));
	tmp = ft_strjoin(dest, " ");
	free(dest);
	dest = ft_strjoin(tmp, src);
	free(tmp);
	return (dest);
}

char	*copy_redir(char *dest, char *src)
{
	if (!src)
		return (NULL);
	if (dest)
		free(dest);
	dest = ft_strdup(src);
	return (dest);
}

void	process_input(t_organize *program, t_program *mini)
{
	int			i;
	int			struct_pos;
	char		**input;
	t_organize *tmp;

	i = -1;
	struct_pos = 0;
	tmp = program;
	input = ft_new_split(mini->user_input, ' ');
	while (input[++i])
	{
		if (ft_strcmp(input[i], "<") == 0 && input[i + 1])
		{
			tmp->input_file = copy_redir(tmp->input_file, input[++i]);
			printf("input_file[%d]: %s\n", struct_pos, tmp->input_file);
		}
		else if (ft_strcmp(input[i], "<<") == 0 && input[i + 1])
		{
			tmp->heredoc_dlm = copy_redir(tmp->heredoc_dlm, input[++i]);
			printf("heredoc_dlm[%d]: %s\n", struct_pos, tmp->heredoc_dlm);
		}
		else if (ft_strcmp(input[i], ">") == 0 && input[i + 1])
		{
			tmp->output_file = copy_redir(tmp->output_file, input[++i]);
			printf("output_file[%d]: %s\n", struct_pos, tmp->output_file);
		}
		else if (ft_strcmp(input[i], ">>") == 0 && input[i + 1])
		{
			tmp->append_file = copy_redir(tmp->append_file, input[++i]);
			printf("append_file[%d]: %s\n", struct_pos, tmp->append_file);
		}
		else if (ft_strcmp(input[i], "|") == 0)
		{
			tmp = tmp->next;
			struct_pos++;
			continue ;
		}
		else
		{
			tmp->cmds = ft_strdup(input[i]);
			printf("cmd_split[%d]: %s\n", struct_pos, tmp->cmds);
			while (input[i + 1] && !is_token(input[i + 1][0]))
				tmp->args = copy_args(tmp->args, input[++i]);
			printf("args_split[%d]: %s\n", struct_pos, tmp->args);
		}
	}
	free_array(input);
}

void	parse_input(t_program *mini, t_organize *program)
{
	if (inside_quotes(mini->user_input, ft_strlen(mini->user_input)) != 0)
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		return ;
	}
	process_input(program, mini);
}
