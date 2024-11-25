/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:10:50 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/23 15:10:20 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

char	*remove_heredoc_quotes(char *input)
{
	t_var	var;
	char	*new_input;

	var.i = size_without_quotes(input);
	var.j = 0;
	new_input = (char *)malloc(sizeof(char) * (var.i + 1));
	if (!new_input)
		return (NULL);
	var.i = -1;
	while (input[++var.i])
	{
		var.c = 0;
		if (input[var.i] == '\'' || input[var.i] == '\"')
		{
			var.c = input[var.i++];
			while (input[var.i] && input[var.i] != var.c)
				new_input[var.j++] = input[var.i++];
		}
		if (input[var.i] != var.c)
			new_input[var.j++] = input[var.i];
	}
	new_input[var.j] = '\0';
	return (new_input);
}

char	*expander_heredoc(char *input)
{
	t_var	var;
	char	*new_str;

	var.i = -1;
	var.k = -1;
	var.size = expanded_size(input);
	new_str = malloc(var.size + 1);
	while (input[++var.i])
	{
		if (input[var.i] == '$')
		{
			var.str = expand_variable(input, &var.i);
			if (!var.str)
				var.str = ft_strdup("");
			var.j = -1;
			while (var.str[++var.j])
				new_str[++var.k] = var.str[var.j];
		}
		else
			new_str[++var.k] = input[var.i];
	}
	new_str[++var.k] = '\0';
	return (new_str);
}

int	heredoc(char *input)
{
	int			fd;
	int			flag;
	char		*line;
	 char		*tmp;

	fd = 0;
	flag = 0;
	if (input[0] == '\'' || input[0] == '\"')
		flag = 1;
	if (input)
	{
		tmp = remove_heredoc_quotes(input);
		printf("heredoc_dlm: %s\n", input);
		fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
		while (1)
		{
			line = readline("> ");
			// if (flag == 0)
			// 	line = expander_heredoc(line);
			if (ft_strcmp(line, tmp) == 0)
				break;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free_ptr(tmp);
	}
	// else if (input && flag == 0)
	// {
	// 	fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// 	while (1)
	// 	{
	// 		line = readline("> ");
	// 		line = expander_heredoc(line);
	// 		// tmp = ft_strdup(line);
	// 		// free(line);
	// 		// printf("line: %s\n", line);
	// 		if (ft_strcmp(line, input) == 0)
	// 			break;
	// 		write(fd, line, ft_strlen(line));
	// 		write(fd, "\n", 1);
	// 	}
	// }
	return (fd);
}
