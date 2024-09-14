/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliman <caliman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/14 23:12:59 by caliman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char **copy_split(t_input_organize *dest, char **src)
{
	t_input_organize *program;
	int i;
	
	program = dest;
	i = 0;
	while (src[i])
	{
		program->cmd_split[i] = ft_strdup(src[i]);
		i++;
	}
	program->cmd_split[i] = NULL;
	return (program->cmd_split);
}*/

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
	int k;
	char **tmp;
	char **split;

	i = -1;
	j = 0;
	k = 0;
	tmp = ft_split(input, ' ');
	if (!tmp)
		return ;
	split = (char **)malloc(sizeof(char *) * ft_strlen(input) + 1);
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
			if (tmp[i + 1] && (!ft_strchr(META_CHARS, tmp[i + 1][0])))
			{
				char *joined;
				joined = ft_strjoin(tmp[i], " ");
				while (tmp[i + 1] && (!ft_strchr(META_CHARS, tmp[i + 1][0])))
				{
					//joined = (char *)realloc(joined, sizeof(char) * (ft_strlen(joined) + ft_strlen(tmp[i + 1]) + 1));
					joined = ft_strjoin(joined, tmp[i + 1]);
					//joined = (char *)realloc(joined, sizeof(char) * (ft_strlen(joined) + 1));
					joined = ft_strjoin(joined, " ");
					printf("cmd_split[%d]: %s\n", j, joined);
					i++;
				}
				split[j] = (char *)malloc(sizeof(char) * ft_strlen(joined) + 1);
				split[j] = ft_strdup(joined);
				free(joined);
				j++;
				k++;
			}
			else
			{
				split[j] = (char *)malloc(sizeof(char) * ft_strlen(tmp[i]) + 1);
				split[j] = ft_strdup(tmp[i]);
				printf("cmd_split[%d]: %s\n", j, split[j]);
				j++;
				k++;
			}		
		}
	}
	split[j] = 0;
	program->cmd_split = (char **)malloc(sizeof(char *) * k + 1);
	program->cmd_split = split;
	//free_array(split);
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
