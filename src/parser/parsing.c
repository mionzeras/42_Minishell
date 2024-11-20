/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/20 22:14:18 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_redir(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((ft_strncmp(input[i], ">", 1) == 0 && !input[i + 1])
			|| (ft_strncmp(input[i], ">>", 2) == 0 && !input[i + 1])
			|| (ft_strncmp(input[i], "<", 1) == 0 && !input[i + 1])
			|| (ft_strncmp(input[i], "<<", 2) == 0 && !input[i + 1]))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", STDERR);
			return (1);
		}
		if ((ft_strncmp(input[i], ">", 1) == 0 && is_token(input[i + 1][0]))
			|| (ft_strncmp(input[i], ">>", 2) == 0 && is_token(input[i + 1][0]))
			|| (ft_strncmp(input[i], "<", 1) == 0 && is_token(input[i + 1][0]))
			|| (ft_strncmp(input[i], "<<", 2) == 0 && is_token(input[i + 1][0])))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", input[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*copy_args(char *dest, char *src)
{
	char	*tmp;
	
	if (!dest)
		return (ft_strdup(src));
	tmp = ft_strjoin(dest, " ");
	free_ptr(dest);
	dest = ft_strjoin(tmp, src);
	free_ptr(tmp);
	return (dest);
}

char	*copy_redir(char *dest, char *src)
{
	if (!src)
		return (NULL);
	if (dest)
		free_ptr(dest);
	dest = ft_strdup(src);
	return (dest);
}

void	process_input(t_organize *program, char *str)
{
	int			i;
	int			list_size;
	char		**input;
	t_organize *tmp;

	i = -1;
	list_size = 0;
	tmp = program;
	input = ft_new_split(str, ' ');
	if (check_empty_redir(input) == 1)
	{
		free_array(input);
		return ;
	}
	while (input[++i])
	{
		input[i] = remove_quotes(input[i]);
		printf("new_input: %s\n", input[i]);
	}
	i = -1;
	while (input[++i])
	{	
		if (ft_strcmp(input[i], "<") == 0 && input[i + 1])
		{
			tmp->input_file = copy_redir(tmp->input_file, input[++i]);
			tmp->fd_in = open(tmp->input_file, O_RDONLY);
			printf("input_file[%d]: %s\n", tmp->list_pos, tmp->input_file);
		}
		else if (ft_strcmp(input[i], "<<") == 0 && input[i + 1])
		{
			tmp->heredoc_dlm = copy_redir(tmp->heredoc_dlm, input[++i]);
			//tmp->fd_in = //heredoc function
			printf("heredoc_dlm[%d]: %s\n", tmp->list_pos, tmp->heredoc_dlm);
		}
		else if (ft_strcmp(input[i], ">") == 0 && input[i + 1])
		{
			tmp->output_file = copy_redir(tmp->output_file, input[++i]);
			tmp->fd_out = open(tmp->output_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			printf("output_file[%d]: %s\n", tmp->list_pos, tmp->output_file);
		}
		else if (ft_strcmp(input[i], ">>") == 0 && input[i + 1])
		{
			tmp->append_file = copy_redir(tmp->append_file, input[++i]);
			tmp->fd_out = open(tmp->append_file, O_RDWR | O_CREAT | O_APPEND, 0644);
			printf("append_file[%d]: %s\n", tmp->list_pos, tmp->append_file);
		}
		else if (ft_strcmp(input[i], "|") == 0)
		{
			if (input[i + 1] == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `|'", STDERR);
				free_array(input);
				return ;
			}
			tmp = tmp->next;
			list_size++;
			tmp->list_pos = list_size;
			printf("\n");
			continue ;
		}
		else
		{
			tmp->cmds = ft_strdup(input[i]);
			printf("cmd_split[%d]: %s\n", tmp->list_pos, tmp->cmds);
			while (input[i + 1] && !is_token(input[i + 1][0]))
				tmp->args = copy_args(tmp->args, input[++i]);
			printf("args_split[%d]: %s\n", tmp->list_pos, tmp->args);
		}
	}
	free_array(input);
}

void	parse_input(char *str, t_organize *program)
{
	if (inside_quotes(str, ft_strlen(str)) != 0)
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		return ;
	}
	printf("user_input: %s\n", str);
	process_input(program, str);
	
}
