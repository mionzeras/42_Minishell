/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/09 20:35:33 by gcampos-         ###   ########.fr       */
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

int ft_array_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void process_token(char *input, t_input_organize *program)
{
	int i;
	char **tmp;

	i = -1;
	tmp = ft_split(input, ' ');
	if (!tmp)
		return ;
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
				if (!program->cmds)
					program->cmds = ft_strdup(tmp[i]);
				else
				{
					size_t len = ft_strlen(program->cmds) + ft_strlen(tmp[i]) + 2;
					program->cmds = ft_realloc(program->cmds, len);
					if (program->cmds)
					{
						ft_strcat(program->cmds, " ");
						ft_strcat(program->cmds, tmp[i]);
					}
					else
						exit(EXIT_FAILURE);
				}
			}
	}
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
