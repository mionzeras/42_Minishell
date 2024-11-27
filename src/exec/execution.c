/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/27 22:43:14 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_cmd(t_program *mini, t_organize *program)
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
	if (is_builtin(program->cmds))
		run_builtin(mini, program);
	else
		exec_cmd(program->cmds, program->args, mini->env_list);
}

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
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
    int 		fd[2];
    int 		in_fd = STDIN; // Entrada inicial, geralmente stdin
	int			last;
    pid_t 		pid;
	

	//fd = malloc(sizeof(int *) * 2);
	// last = ft_lstsize    esta recebe t_list, vou refazer para receber t_organize
    while (tmp)
    {
        if (tmp->next && pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		pid = fork();
		if (pid == 0) // Processo filho
		{
			if (program->list_pos == 0)
			{
				close(fd[0]); // Fecha leitura do pipe no filho
				if (program->fd_in != -1)
					dup2(program->fd_in, STDIN_FILENO);
				if (tmp->next && program->fd_out == -1)
					dup2(fd[1], STDOUT_FILENO);
				else if (program->fd_out != -1)
				{
					dup2(program->fd_out, STDOUT_FILENO);
					close(fd[1]);
				}
			}
			}
			else if (program->list_pos == (last - 1))
			{
				//abre os fds do ultimo no
			}
			else
			{
				//abre os fds dos nos do meio
			}
			if (is_builtin(tmp->cmds))
			{
				run_builtin(mini, tmp);
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


