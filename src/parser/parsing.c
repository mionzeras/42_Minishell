/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/11 19:36:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//t_input_organize *prog_tmp;
	int i;
	int j;
	char *input_tmp;
	char **tmp;

	//prog_tmp = program;
	i = -1;
	j = 0;
	input_tmp = ft_strdup(input);
	tmp = ft_split(input_tmp, ' ');
	free(input_tmp);
	if (!tmp)
		return ;
	program->cmd_split = (char **)malloc(sizeof(char **) * 2);
	while (tmp[++i])
	{
		if (ft_strcmp(tmp[i], "<") == 0 && tmp[i + 1])
			program->input_file = ft_strdup(tmp[++i]);	
		else if (ft_strcmp(tmp[i], "<<") == 0 && tmp[i + 1])
			program->heredoc_delimiter = ft_strdup(tmp[++i]);
		else if (ft_strcmp(tmp[i], ">") == 0 && tmp[i + 1])
			program->output_file = ft_strdup(tmp[++i]);
		else if (ft_strcmp(tmp[i], ">>") == 0 && tmp[i + 1])
			program->append_file = ft_strdup(tmp[++i]);
		else
		{
			program->cmd_split = ft_realloc(program->cmd_split, sizeof(char *) * j, sizeof(char *) * (j + 2));
			program->cmd_split[j] = ft_strdup(tmp[i]);
			j++;
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
}
