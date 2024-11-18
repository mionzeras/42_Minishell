/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/18 21:30:00 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

void	redir_pipes(t_organize *program)
{
	if (program->fd_in != -1)
	{
		dup2(program->fd_in, STDIN);
		close(program->fd_in);
	}
	if (program->fd_out != -1)
	{
		dup2(program->fd_out, STDOUT);
		close(program->fd_out);
	}
}
	
executor(t_organize *program, t_program *mini)
{
	t_organize	*tmp;
	int			fd[2];

	if (pipe(fd) == -1)
		ft_error("Pipe");

	tmp = program;

	while(tmp)
	{
		if (tmp->next && (tmp->append_file == -1 || !tmp->output_file == -1))
			dup2(fd[1], STDOUT);
		if (tmp->list_pos != 0 && tmp->fd_in == -1)
			dup2(fd[0], STDIN);
		redir_pipes(tmp);
		if (is_builtin(tmp->cmds))
			ft_exec_builtin(tmp, mini);
		else
			ft_execve(tmp, mini);
		tmp = tmp->next;
	}
}
