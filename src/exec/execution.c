/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/03 23:58:31 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void setup_redirections(t_organize *cmd, int pipe_read, int pipe_write)
{
	// Redireciona entrada
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (pipe_read != -1)
		dup2(pipe_read, STDIN_FILENO);

	// Redireciona saída
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (pipe_write != -1)
		dup2(pipe_write, STDOUT_FILENO);
}


void close_unused_fds(int fd_in, int fd_out, int pipe_read, int pipe_write)
{
	if (fd_in != -1 && fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != -1 && fd_out != STDOUT_FILENO)
		close(fd_out);
	if (pipe_read != -1 && pipe_read != STDIN_FILENO)
		close(pipe_read);
	if (pipe_write != -1 && pipe_write != STDOUT_FILENO)
		close(pipe_write);
}


// void	exec_one_cmd(t_program *mini, t_organize *program, int fd1, int fd2)
// {
// 	pid_t	pid;
	
// 	if (!program->cmds)
// 		return ;
// 	if (program->fd_in != -1)
// 	{
// 		printf("tem redirecionamento de entrada\n");
// 		printf("fd_in: %d\n", program->fd_in);
// 		dup2(program->fd_in, STDIN);
// 		close(program->fd_in);
// 	}
// 	if (program->fd_out != -1)
// 	{
// 		printf("tem redirecionamento de saida\n");
// 		printf("fd_out: %d\n", program->fd_out);
// 		dup2(program->fd_out, STDOUT);
// 		close(program->fd_out);
// 	}
// 	if (is_builtin(program->cmds))
// 		run_builtin(mini, program, fd1, fd2);
// 	else
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			if (!exec_cmd(program->cmds, program->args, mini->env_list))
// 			{
// 				free_organize(program);
// 				delete_list(mini->env_list);
// 				reset_fds(fd1, fd2, 1);
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 		}
// 	}
// 	reset_fds(fd1, fd2, 0);
// }

void exec_one_cmd(t_program *mini, t_organize *program, int fd1, int fd2)
{
	pid_t pid;

	if (!program->cmds)
		return;

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
		if (pid == 0) // Processo filho
		{
			if (!exec_cmd(program->cmds, program->args, mini->env_list))
			{
				perror("execve");
				free_organize(program);
				delete_list(mini->env_list);
				reset_fds(fd1, fd2, 1);
				exit(EXIT_FAILURE);
			}
		}
		else // Processo pai
		{
			waitpid(pid, NULL, 0);
		}
	}

	reset_fds(fd1, fd2, 0); // Restaura FDs para o próximo comando
}

void	reset_pipe(int pipe[])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	redirect_io(t_organize *program, int pipe[], int status)
{
	if (program->list_pos == 0)
	{
		if (status == 1)
			close(pipe[0]);
		if (program->fd_in != -1)
			dup2(program->fd_in, STDIN_FILENO);
		else if (program->fd_out != -1)
		{
			dup2(program->fd_out, STDOUT_FILENO);
			if (status == 1)
				close(pipe[1]);
		}
		else if (program->fd_out == -1 && program->next && status == 1)
			dup2(pipe[1], STDOUT_FILENO);
	}
	else if (program->list_pos == (ft_list_size(program) - 1))
	{
		if (status == 1)
			close(pipe[1]);
		if (program->fd_in != -1)
		{
			dup2(program->fd_in, STDIN_FILENO);
			if (status == 1)
				close(pipe[0]);
		}
		else if (program->fd_in == -1 && status == 1)
			dup2(pipe[0], STDIN_FILENO);
		if (program->fd_out != -1)
			dup2(program->fd_out, STDOUT_FILENO);
	}
	else
	{
		if (program->fd_in != -1)
		{
			dup2(program->fd_in, STDIN_FILENO);
			if (status == 1)
				close(pipe[0]);
		}
		else if (program->fd_in == -1 && status == 1)
			dup2(pipe[0], STDIN_FILENO);
		if (program->fd_out != -1)
		{
			dup2(program->fd_out, STDOUT_FILENO);
			if (status == 1)
				close(pipe[1]);
		}
		else
			dup2(pipe[1], STDOUT_FILENO);
	}
}

void execute_pipeline(t_program *mini, t_organize *program_list, int fd1, int fd2)
{
    int pipe_fds[2];
    pid_t pid;

    while (program_list)
    {
        // Configura pipes, se necessário
        if (program_list->next)
        {
            if (pipe(pipe_fds) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            // program_list->fd_out = pipe_fds[1];
            // program_list->next->fd_in = pipe_fds[0];
        }
		if (program_list->next)
        	redirect_io(program_list, pipe_fds, 1);
		else
			redirect_io(program_list, pipe_fds, 0);
		if (is_builtin(program_list->cmds))
		{
			run_builtin(mini, program_list, fd1, fd2);
			program_list = program_list->next;
			continue ;
		}
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // Processo filho
        {
            if (!exec_cmd(program_list->cmds, program_list->args, mini->env_list))
            {
                free_organize(program_list);
                delete_list(mini->env_list);
                reset_fds(fd1, fd2, 1);
                exit(EXIT_FAILURE);
            }
        }
        else // Processo pai
        {
            if (program_list->fd_out != -1)
                close(program_list->fd_out);

            waitpid(pid, NULL, 0);
        }
		if (program_list->fd_in != -1)
			close(program_list->fd_in);
		if (program_list->fd_out != -1)
			close(program_list->fd_out);
		if (program_list->next)
			reset_pipe(pipe_fds);
        program_list = program_list->next;
    }
    reset_fds(fd1, fd2, 0);
}

// void execute_pipeline(t_program *mini, t_organize *program_list, int fd1, int fd2)
// {
// 	int pipe_fds[2];
// 	int prev_fd = -1;

// 	while (program_list)
// 	{
// 		// Configura pipes, se necessário
// 		if (program_list->next)
// 		{
// 			if (pipe(pipe_fds) == -1)
// 			{
// 				perror("pipe");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		// Redireciona entradas/saídas
// 		if (prev_fd != -1)
// 		{
// 			dup2(prev_fd, STDIN_FILENO);
// 			close(prev_fd);
// 		}
// 		if (program_list->next)
// 			dup2(pipe_fds[1], STDOUT_FILENO);

// 		// Executa comando
// 		exec_one_cmd(mini, program_list, fd1, fd2);

// 		// Atualiza FDs para o próximo comando
// 		if (program_list->next)
// 			close(pipe_fds[1]);
// 		prev_fd = pipe_fds[0];

// 		program_list = program_list->next;
// 	}

// 	// // Fecha o último FD do pipe
// 	// if (prev_fd != -1)
// 	// 	close(prev_fd);

// 	// Restaura FDs originais
// 	reset_fds(fd1, fd2, 1);
// }


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

// void	redir_pipes(t_organize *program)
// {
// 	if (program->fd_in != -1)
// 	{
// 		dup2(program->fd_in, STDIN);
// 		close(program->fd_in);
// 	}
// 	if (program->fd_out != -1)
// 	{
// 		dup2(program->fd_out, STDOUT);
// 		close(program->fd_out);
// 	}
// }

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

// //Fim: Funçoes para reduzir a função executor e deixar com 25 linhas




// void	executor(t_organize *program, t_program *mini)
// {
// 	t_organize	*tmp;
// 	pid_t		pid;
// 	int			fd[2];
// 	int			last;
// 	//int		in_fd = STDIN; // Entrada inicial, geralmente stdin

// 	//fd = malloc(sizeof(int *) * 2);
// 	tmp = program;
// 	last = ft_list_size(program);
// 	while (tmp)
// 	{
// 		if (tmp->next && pipe(fd) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0) // Processo filho
// 		{
// 			printf("estou no filho\n");
// 			chield_process(tmp, mini, fd, last);
// 		}
// 		else // Processo pai
// 		{
// 			printf("estou no pai\n");
// 			waitpid(pid, NULL, 0); // Aguarda o processo filho terminar, WNOHANG não bloqueia o pai
// 			dad_process(program, fd);
// 		}
// 		// reset_fds(program); // Reseta os descritores de arquivo para stdin e stdout
// 		tmp = tmp->next; // Avança para o próximo comando
// 	}
// }

void exec_cmd_list(t_program *mini, t_organize *program_list, int fd1, int fd2)
{
	int pipe_fds[2] = {-1, -1};
	int prev_pipe_read = -1;
	pid_t pid;

	while (program_list)
	{
		// Cria pipe para o próximo comando, se necessário
		if (program_list->next && pipe(pipe_fds) == -1)
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
			setup_redirections(program_list, prev_pipe_read, pipe_fds[1]);
			close_unused_fds(program_list->fd_in, program_list->fd_out, prev_pipe_read, pipe_fds[1]);
			if (is_builtin(program_list->cmds))
				run_builtin(mini, program_list, fd1, fd2);
			else if (!exec_cmd(program_list->cmds, program_list->args, mini->env_list))
			{
				free_organize(program_list);
				delete_list(mini->env_list);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}

		// Processo pai
		close(pipe_fds[1]); // Fecha lado de escrita do pipe
		if (prev_pipe_read != -1)
			close(prev_pipe_read); // Fecha lado de leitura do pipe anterior

		prev_pipe_read = pipe_fds[0]; // Atualiza lado de leitura para o próximo comando
		pipe_fds[0] = pipe_fds[1] = -1;

		program_list = program_list->next;
	}

	// Fecha o último pipe
	if (prev_pipe_read != -1)
		close(prev_pipe_read);

	// Aguarda todos os processos filhos
	while (wait(NULL) > 0);
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