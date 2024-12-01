/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:10:50 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/01 20:30:48 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	free_all(char *tmp, char *filename, char *line)
{
	free_ptr(tmp);
	free_ptr(filename);
	free_ptr(line);
}

char	*generate_filename(int h)
{
	char	*h_str;
	char	*filename;

	h_str = ft_itoa(h);
	filename = ft_strjoin(h_str, ".tmp");
	free_ptr(h_str);
	return (filename);
}

void	process_line(int fd, char *line, int expand, t_env *env)
{
	char	*expanded;

	if (expand)
	{
		expanded = expander(line, env);
		write(fd, expanded, ft_strlen(expanded));
		free_ptr(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	heredoc(char *input, t_env *env)
{
	t_var		var;
	char		*line;
	char		*tmp;
	char		*filename;
	static int	h;

	var.k = (input[0] == '\'' || input[0] == '\"');
	h++;
	tmp = ft_strdup(input);
	tmp = remove_quotes(tmp);
	filename = generate_filename(h);
	var.i = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.i < 0)
		return (free_ptr(tmp), free_ptr(filename),
			perror("Error opening file"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, tmp) == 0)
			break ;
		process_line(var.i, line, !var.k, env);
	}
	free_all(tmp, filename, line);
	close(var.i);
	var.i = open(filename, O_RDONLY);
	return (var.i);
}
