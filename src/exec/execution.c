/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/04 18:25:06 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_cmd(t_program *mini, t_organize *program, int fd1, int fd2)
{
	pid_t	pid;
	
	if (!program->cmds)
		return ;
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
		run_builtin(mini, program, fd1, fd2);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (!exec_cmd(program->cmds, program->args, mini->env_list))
			{
				free_organize(program);
				delete_list(mini->env_list);
				reset_fds(fd1, fd2, 1);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	reset_fds(fd1, fd2, 0);
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

void	reset_fds(int fd1, int fd2, int status)
{
	dup2(fd1, STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	if (status == 1)
	{
		close(fd1);
		close(fd2);
	}
}



//Inicio: Funçoes para reduzir a função executor e deixar com 25 linhas

// void	exec_first(int fd[], t_organize *program)
// {
// 	close(fd[0]); // Fecha leitura do pipe de entrada no filho
// 	if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
// 		dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
// 	if (program->fd_out == -1) // Se não houver redirecionamento de saída
// 		dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
// 	else if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
// 	{
// 		dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
// 		close(fd[1]); // Fecha escrita do pipe no filho	
// 	}
// }

// void	exec_last(int fd[], t_organize *program)
// {
// 	close(fd[1]); // Fecha escrita do pipe no filho
// 	if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
// 	{
// 		dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
// 		close(fd[0]); // Fecha leitura do pipe de entrada no filho
// 	}
// 	else
// 		dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
// 	if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
// 		dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
// }

// void	exec_middle(int fd[], t_organize *program)
// {
// 	if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
// 	{
// 		dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
// 		close(fd[0]); // Fecha leitura do pipe de entrada no filho
// 	}
// 	else
// 		dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
// 	if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
// 	{
// 		dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
// 		close(fd[1]); // Fecha escrita do pipe no filho
// 	}
// 	else
// 		dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
// }

// void	chield_process(t_organize *tmp, t_program *mini, int fd[], int last)
// {	
// 	if (tmp->list_pos == 0) // Se for o primeiro comando
// 		exec_first(fd, tmp);
// 	else if (tmp->list_pos == (last -1)) // se for o ultimo comando
// 		exec_last(fd, tmp);
// 	else // Se for um comando intermediário
// 		exec_middle(fd, tmp);
// 	if (is_builtin(tmp->cmds))
// 	{
// 		printf("estou no builtin\n");
// 		run_builtin(mini, tmp, fd[0], fd[1]);
// 		exit(0); // Encerra o processo filho após executar o builtin
// 	}
// 	else
// 		exec_cmd(tmp->cmds, tmp->args, mini->env_list);
// }

// void	dad_process(t_organize *program, int fd[])
// {
// 	if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
// 		close(program->fd_in); // Fecha o arquivo de entrada
// 	if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
// 		close(program->fd_out); // Fecha o arquivo de saída
// 	close(fd[0]); // Fecha leitura do pipe no pai
// 	close(fd[1]); // Fecha escrita do pipe no pai
// }

//Fim: Funçoes para reduzir a função executor e deixar com 25 linhas

void exec_with_pipes(t_program *mini, t_organize *program)
{
    int i = 0;
    int num_pipes = mini->pipes;
    int pipes[num_pipes][2]; // Array de pipes
    pid_t pid;

    // Criar os pipes necessários
    for (i = 0; i < num_pipes; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    i = 0;
    t_organize *curr_cmd = program;
    while (curr_cmd)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // Processo filho
        {
            // Configuração dos pipes
            if (i > 0) // Não é o primeiro comando
            {
                dup2(pipes[i - 1][0], STDIN_FILENO); // Ler do pipe anterior
                close(pipes[i - 1][0]);
            }
            if (i < num_pipes) // Não é o último comando
            {
                dup2(pipes[i][1], STDOUT_FILENO); // Escrever no pipe atual
                close(pipes[i][1]);
            }
			redir_pipes(curr_cmd);
            // Fechar os pipes que não são usados neste processo
            for (int j = 0; j < num_pipes; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Executar comando
            if (!exec_cmd(curr_cmd->cmds, curr_cmd->args, mini->env_list))
            {
                free_organize(program);
                delete_list(mini->env_list);
                exit(EXIT_FAILURE);
            }
        }
        curr_cmd = curr_cmd->next; // Próximo comando
        i++;
    }

    // Fechar todos os pipes no processo pai
    for (i = 0; i < num_pipes; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Esperar todos os processos filhos
    for (i = 0; i < mini->pipes; i++)
        wait(NULL);
}


//Processo Filho: copia de segurança para reduzir a função executor

/*
if (program->list_pos == 0) // Se for o primeiro comando
			{
				exec_first(fd, program);
			// 	close(fd[0]); // Fecha leitura do pipe de entrada no filho
			// 	if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
			// 		dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
			// 	if (program->fd_out == -1) // Se não houver redirecionamento de saída
			// 		dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
			// 	else if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
			// 	{
			// 		dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
			// 		close(fd[1]); // Fecha escrita do pipe no filho	
			// 	}
			}
			else if (program->list_pos == (last -1)) // se for o ultimo comando
			{
				exec_last(fd, program);
				// close(fd[1]); // Fecha escrita do pipe no filho
				// if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
				// {
				// 	dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
				// 	close(fd[0]); // Fecha leitura do pipe de entrada no filho
				// }
				// else
				// 	dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
				// if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
				// 	dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
			}
			else // Se for um comando intermediário
			{
				exec_middle(fd, program);
				// if (program->fd_in != -1) // Se houver redirecionamento de entrada (arquivo)
				// {
				// 	dup2(program->fd_in, STDIN_FILENO); // Redireciona a entrada para o arquivo
				// 	close(fd[0]); // Fecha leitura do pipe de entrada no filho
				// }
				// else
				// 	dup2(fd[0], STDIN_FILENO); // Redireciona a entrada para o pipe
				// if (program->fd_out != -1) // Se houver redirecionamento de saída (arquivo)
				// {
				// 	dup2(program->fd_out, STDOUT_FILENO); // Redireciona a saída para o arquivo
				// 	close(fd[1]); // Fecha escrita do pipe no filho
				// }
				// else
				// 	dup2(fd[1], STDOUT_FILENO); // Redireciona a saída para o pipe
			}
			if (is_builtin(tmp->cmds))
			{
				printf("estou no builtin\n");
				run_builtin(mini, tmp);
				exit(0); // Encerra o processo filho após executar o builtin
			}
			else
				exec_cmd(tmp->cmds, tmp->args, mini->env_list);
*/