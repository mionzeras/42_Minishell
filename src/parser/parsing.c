/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/16 17:02:13 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *join_cmd_arg(char *cmd, char *arg)
{
	char *joined;
	char *tmp;

	tmp = ft_strjoin(cmd, " ");
	joined = ft_strjoin(tmp, arg);
	free(tmp);
	free (cmd);
	return (joined);
}

char *copy_redir(char *dest, char *src)
{
	if (!src)
		return (NULL);
	if (dest)
		free(dest);
	dest = ft_strdup(src);
	return (dest);
}

void  process_token(char *input, t_input_organize *program)
{
	int i;
	int j;
	char **tmp;
	char *joined;
	char **split;

	i = -1;
	j = 0;
	tmp = ft_split(input, ' ');
	if (!tmp)
		return ;
	split = (char **)malloc(sizeof(char *) * ft_strlen(input) + 1);
	while (tmp[++i])
	{
		if (ft_strcmp(tmp[i], "<") == 0 && tmp[i + 1])
			program->input_file = copy_redir(program->input_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], "<<") == 0 && tmp[i + 1])
			program->heredoc_delimiter = copy_redir(program->heredoc_delimiter, tmp[++i]);
		else if (ft_strcmp(tmp[i], ">") == 0 && tmp[i + 1])
			program->output_file = copy_redir(program->output_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], ">>") == 0 && tmp[i + 1])
			program->append_file = copy_redir(program->append_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], "|") == 0)
			program->pipes++;
		else
		{
			if (tmp[i + 1] && (!ft_strchr(META_CHARS, tmp[i + 1][0])))
			{
				joined = ft_strdup(tmp[i]);
				while (tmp[i + 1] && (!ft_strchr(META_CHARS, tmp[i + 1][0])))
				{
					joined = join_cmd_arg(joined, tmp[i + 1]);
					printf("cmd_split[%d]: %s\n", j, joined);
					i++;
				}
				split[j] = ft_strdup(joined);
				free(joined);
				j++;
			}
			else
			{
				split[j] = ft_strdup(tmp[i]);
				printf("cmd_split[%d]: %s\n", j, split[j]);
				j++;
			}		
		}
	}
	split[j] = NULL;
	program->cmd_split = split;
	free_array(tmp);
}

void	parse_input(t_program *mini, t_input_organize *program)
{
	if (!check_quotes(mini->user_input))
	{
		ft_printf("Error: minishell does not support unclosed quotes\n");
		return ;
	}
	process_token(mini->user_input, program);
	printf("user_input: %s\n", mini->user_input);
	printf("input_file: %s\n", program->input_file);
	printf("output_file: %s\n", program->output_file);
	printf("append_file: %s\n", program->append_file);
	printf("heredoc_delimiter: %s\n", program->heredoc_delimiter);
	printf("pipes: %d\n", program->pipes);
}
