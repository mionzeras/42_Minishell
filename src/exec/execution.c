/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/29 12:06:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_cmd(t_program *mini, t_organize *program)
{
	if (program->fd_in != -1)
	{
		dup2(program->fd_in, STDIN);
		// close(program->fd_in);
	}
	if (program->fd_out != -1)
	{
		dup2(program->fd_out, STDOUT);
		// close(program->fd_out);
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

void	reset_fds(t_organize *program)
{
	if (program->fd_in != -1)
	{
		dup2(STDIN, program->fd_in);
		close(program->fd_in);
	}
	if (program->fd_out != -1)
	{
		dup2(STDOUT, program->fd_out);
		close(program->fd_out);
	}
}

void	executor(t_organize *program, t_program *mini)
{
    t_organize *tmp = program;
    int 		fd[2];
    // int 		in_fd = STDIN; // Entrada inicial, geralmente stdin
	int			last;
    pid_t 		pid;
	

	//fd = malloc(sizeof(int *) * 2);
	last = ft_list_size(program);
    while (tmp)
    {
        if (tmp->next && pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Processo filho
		{
			printf("estou no filho\n");
			if (program->list_pos == 0) // Se for o primeiro comando
			{
				close(fd[0]); // Fecha leitura do pipe de entrada no filho
				if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
					dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
				if (program->fd_out == -1) // Se não houver redirecionamento de saída
					dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
				else if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
				{
					dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
					close(fd[1]); // Fecha escrita do pipe no filho	
				}
			}
			else if (program->list_pos == (last -1)) // se for o ultimo comando
			{
				close(fd[1]); // Fecha escrita do pipe no filho
				if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
				{
					dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
					close(fd[0]); // Fecha leitura do pipe de entrada no filho
				}
				else
					dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
				if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
					dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
			}
			else // Se for um comando intermediário
			{
				if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
				{
					dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
					close(fd[0]); // Fecha leitura do pipe de entrada no filho
				}
				else
					dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
				if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
				{
					dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
					close(fd[1]); // Fecha escrita do pipe no filho
				}
				else
					dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
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
			printf("estou no pai\n");
			waitpid(pid, NULL, 0); // Aguarda o processo filho terminar, WNOHANG não bloqueia o pai
			if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
				close(program->fd_in); // Fecha o arquivo de entrada
			if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
				close(program->fd_out); // Fecha o arquivo de saída
			close(fd[0]); // Fecha leitura do pipe no pai
			close(fd[1]); // Fecha escrita do pipe no pai
		}
		// reset_fds(program); // Reseta os descritores de arquivo para stdin e stdout
        tmp = tmp->next; // Avança para o próximo comando
    }
}


