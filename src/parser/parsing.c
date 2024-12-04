/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:39:34 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/02 23:16:28 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes_list(t_organize **program)
{
	t_organize	*tmp;
	int			i;

	tmp = *program;
	while (tmp)
	{
		if (tmp->cmds)
			tmp->cmds = remove_quotes(tmp->cmds);
		i = ft_strlen(tmp->cmds);
		printf("size of cmds: %d\n", i);
		printf("cmds[%d]rmq: %s\n", tmp->list_pos, tmp->cmds);
		if (tmp->args)
			tmp->args = remove_quotes(tmp->args);
		// if (tmp->input_file)
		// 	tmp->input_file = remove_quotes(tmp->input_file);
		// if (tmp->output_file)
		// 	tmp->output_file = remove_quotes(tmp->output_file);
		// if (tmp->append_file)
		// 	tmp->append_file = remove_quotes(tmp->append_file);
		// if (tmp->heredoc_dlm)
		// 	tmp->heredoc_dlm = remove_quotes(tmp->heredoc_dlm);
		tmp = tmp->next;
	}
}

int	check_empty_redir(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_strncmp(str[i], ">", 1) == 0 && !str[i + 1])
			|| (ft_strncmp(str[i], ">>", 2) == 0 && !str[i + 1])
			|| (ft_strncmp(str[i], "<", 1) == 0 && !str[i + 1])
			|| (ft_strncmp(str[i], "<<", 2) == 0 && !str[i + 1]))
		{
			print_error("Syntax error near unexpected token", 2); //verificar texto e codigo de erro (2 ou 258?)
			return (1);
		}
		if ((ft_strncmp(str[i], ">", 1) == 0 && is_token(str[i + 1][0]))
			|| (ft_strncmp(str[i], ">>", 2) == 0 && is_token(str[i + 1][0]))
			|| (ft_strncmp(str[i], "<", 1) == 0 && is_token(str[i + 1][0]))
			|| (ft_strncmp(str[i], "<<", 2) == 0 && is_token(str[i + 1][0])))
		{
			print_error("Syntax error near unexpected token", 2); //verificar texto e codigo de erro (2 ou 258?)
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
	{
		dest = ft_strdup(src);
		return (dest);
	}
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

int	process_input(t_organize *program, char **str, t_env *env)
{
	int			i;
	int			list_size;
	char		**input;
	t_organize	*tmp;

	i = -1;
	list_size = 0;
	tmp = program;
	input = ft_new_split(*str, ' ');
	if (check_empty_redir(input) == 1)
	{
		free_array(input);
		return (1);
	}
	i = -1;
	while (input[++i])
	{
		if (ft_strcmp(input[i], "<") == 0 && input[i + 1])
		{
			i++;
			if (access(input[i], F_OK) != 0)
			{
				print_error("No such file or directory", 2); //verificar texto e codigo de erro (2 ou 258?)
				free_array(input);
				return (1);
			}
			if (tmp->fd_in != -1)
			{
				close(tmp->fd_in);
				tmp->fd_in = -1;
			}
			input[i] = remove_quotes(input[i]);
			tmp->fd_in = open(input[i], O_RDONLY);
			printf("input_file[%d]: %s\n", tmp->list_pos, input[i]);
		}
		else if (ft_strcmp(input[i], "<<") == 0 && input[i + 1])
		{
			i++;
			if (tmp->fd_in != -1)
			{
				close(tmp->fd_in);
				tmp->fd_in = -1;
			}
			tmp->fd_in = heredoc(input[i], env);
			printf("fd_in[%d]: %d\n", tmp->list_pos, tmp->fd_in);
		}
		else if (ft_strcmp(input[i], ">") == 0 && input[i + 1])
		{
			i++;
			if (tmp->fd_out != -1)
			{
				close(tmp->fd_out);
				tmp->fd_out = -1;
			}
			input[i] = remove_quotes(input[i]);
			tmp->fd_out = open(input[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
			printf("output_file[%d]: %s\n", tmp->list_pos, input[i]);
		}
		else if (ft_strcmp(input[i], ">>") == 0 && input[i + 1])
		{
			i++;
			if (tmp->fd_out != -1)
			{
				close(tmp->fd_out);
				tmp->fd_out = -1;
			}
			input[i] = remove_quotes(input[i]);
			tmp->fd_out = open(input[i], O_RDWR | O_CREAT | O_APPEND, 0644);
			printf("append_file[%d]: %s\n", tmp->list_pos, input[i]);
		}
		else if (ft_strcmp(input[i], "|") == 0)
		{
			if (input[i + 1] == NULL)
			{
				print_error("syntax error near unexpected token '|'", 2); //verificar texto e codigo de erro (2 ou 258?)
				free_array(input);
				return (1);
			}
			tmp = tmp->next;
			list_size++;
			tmp->list_pos = list_size;
			printf("\n");
			continue ;
		}
		else
		{
			if (tmp->cmds == NULL)
			{
				input[i] = remove_quotes(input[i]);
				tmp->cmds = ft_strdup(input[i]);
				printf("cmd_split[%d]: %s\n", tmp->list_pos, tmp->cmds);
			}
			else
			{
				input[i] = remove_quotes(input[i]);
				tmp->args = copy_args(tmp->args, input[i]);
				printf("args_split[%d]: %s\n", tmp->list_pos, tmp->args);
			}
		}
	}
	free_array(input);
	return (0);
}

int	parse_organize(t_organize *program, char *str, t_env *env)
{
	if (inside_quotes(str, ft_strlen(str)) != 0)
	{
		print_error("syntax error with open quotes", 2); //verificar texto e codigo de erro (2 ou 258?)
		return (1);
	}
	printf("user_input: %s\n", str);
	return (process_input(program, &str, env));
}
