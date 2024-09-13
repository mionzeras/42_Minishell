/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/13 12:17:21 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *copy(char *dest, char *src)
{
	if (!src)
		return (NULL);
	if (dest)
		free(dest);
	dest = ft_strdup(src);
	return (dest);
	
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

void  process_token(char *input, t_input_organize *program)
{
	int i;
	int j;
	char **tmp;

	i = -1;
	j = 0;
	tmp = ft_split(input, ' ');
	if (!tmp)
		return ;
	program->cmd_split = (char **)malloc(sizeof(char **) * 2);
	while (tmp[++i])
	{
		if (ft_strcmp(tmp[i], "<") == 0 && tmp[i + 1])
			program->input_file = copy(program->input_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], "<<") == 0 && tmp[i + 1])
			program->heredoc_delimiter = copy(program->heredoc_delimiter, tmp[++i]);
		else if (ft_strcmp(tmp[i], ">") == 0 && tmp[i + 1])
			program->output_file = copy(program->output_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], ">>") == 0 && tmp[i + 1])
			program->append_file = copy(program->append_file, tmp[++i]);
		else if (ft_strcmp(tmp[i], "|") == 0)
			program->pipes++;
		else
		{
			if (tmp[i + 1] && (tmp[i + 1][0] != '<' && tmp[i + 1][0] != '>' && tmp[i + 1][0] != '|'))
			{
				program->cmd_split = ft_realloc(program->cmd_split, sizeof(char *) * j, sizeof(char *) * (j + 2));
				char *joined = ft_strjoin(tmp[i], " ");
				program->cmd_split[j] = ft_strjoin(joined, tmp[i + 1]);
				free(joined);
				printf("cmd_split[%d]: %s\n", j, program->cmd_split[j]);
				j++;
				i++;
			}
			else
				{
				program->cmd_split = ft_realloc(program->cmd_split, sizeof(char *) * j, sizeof(char *) * (j + 2));
				program->cmd_split[j] = ft_strdup(tmp[i]);
				printf("cmd_split[%d]: %s\n", j, program->cmd_split[j]);
				j++;
				}		
		}
	}
	if (program->cmd_split)
		program->cmd_split[j] = NULL;
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
