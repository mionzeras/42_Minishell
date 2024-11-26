/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/26 16:30:32 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtin(t_organize *program, t_program *mini)
{
	if (ft_strcmp(program->cmds, "echo") == 0)
		ft_echo(program);
	else if (ft_strcmp(program->cmds, "cd") == 0)
		ft_cd(mini, program);
	else if (ft_strcmp(program->cmds, "pwd") == 0)
		ft_pwd(program);
	else if (ft_strcmp(program->cmds, "unset") == 0)
		ft_unset(mini, program);
	else if (ft_strcmp(program->cmds, "env") == 0)
		print_env_list(mini->env_list);
	else if (ft_strcmp(program->cmds, "export") == 0)
		ft_export(mini, program->args);
}

int	is_builtin(char *command)
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

void	executor(t_organize *program, t_program *mini)
{
    t_organize *tmp = program;
    int *fd[2];
    int in_fd = STDIN; // Entrada inicial, geralmente stdin
    pid_t pid;

    while (tmp)
    {
        if (tmp->next && pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		while (tmp)
		if (pid == 0) // Processo filho
		{
			if (tmp->fd_in != -1)
				dup2(tmp->fd_in, STDIN);
			else if (in_fd != STDIN)
			 	dup2(in_fd, STDIN);
			if (tmp->fd_out != -1)
				dup2(tmp->fd_out, STDOUT);
			else if (tmp->next)
				dup2(fd[1], STDOUT);
			if (is_builtin(tmp->cmds))
			{
				ft_exec_builtin(tmp, mini);
				exit(0); // Encerra o processo filho após executar o builtin
			}
			else
				exec_cmd(tmp->cmds, tmp->args, mini->env_list);
		}
		else // Processo pai
		{
			waitpid(pid, NULL, 0); // Aguarda o término do filho
			close(fd[1]); // Fecha escrita do pipe no pai
			if (in_fd != STDIN)
				close(in_fd);

			in_fd = fd[0]; // Configura a entrada para o próximo comando
		}
        tmp = tmp->next; // Avança para o próximo comando
    }
}


