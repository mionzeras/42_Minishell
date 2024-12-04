/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:38:43 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/04 23:52:27 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int fd_in, int count_pipes, int fork_pid)
{
	int	i;
	int	status;

	i = 0;
	close(fd_in);
	if (waitpid(fork_pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
	}
	while (i < count_pipes)
	{
		wait(&status);
		i++;
	}
}

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
		// ft_handle_signals(CHILD);
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
			parent_process(fd1, mini->pipes, pid);
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

void exec_with_pipes(t_program *mini, t_organize *program)
{
    int i = 0;
    int num_pipes = mini->pipes;
    int pipes[num_pipes][2]; // Array de pipes
    pid_t pid;
	
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
        // ft_handle_signals(IGNORE);
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < num_pipes)
                dup2(pipes[i][1], STDOUT_FILENO);
            for (int j = 0; j < num_pipes; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            redir_pipes(curr_cmd);
            if (!exec_cmd(curr_cmd->cmds, curr_cmd->args, mini->env_list))
            {
                free_organize(program);
                delete_list(mini->env_list);
                exit(EXIT_FAILURE);
            }
        }
        curr_cmd = curr_cmd->next;
        i++;
    }
    for (i = 0; i < num_pipes; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    while (wait(NULL) > 0);
}
