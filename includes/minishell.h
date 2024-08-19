/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:26:57 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/19 00:42:57 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MINI_MSG "\e[1;93mminishell\033[91m$ \033[0m"

//types of commands
typedef enum e_type
{
	PIPE,
	LESS,
	LESS_LESS,
	GREATER,
	GREATER_GREATER,
}	t_type;

//redirections
typedef struct s_redirection
{
	char			*input_file;
	char			*heredoc_file;
	char			*truncate_file;
	char			*append_file;
}	t_redirection;

//commands
typedef struct s_token
{
	char			**cmds;
	struct s_token	*next;
	t_type			*types;
}	t_token;

//status of the last command
typedef struct s_status
{
	int				last_exit_status;
}	t_status;

//main struct
typedef struct s_program
{
	char			**env;
	char			*user_input;
	char			*pwd;
	char			*old_pwd;
	char 			**path;
	int				stop;
	int				stdin_copy;
	int				stdout_copy;
	t_redirection	redirection;
	t_token			*token;
	t_status		status;
}	t_program;

//parsing.c
void	parse_input(t_program *mini);

//clean.c
//void	*ft_memdel(void *ptr);
void	free_array(char **array);
void	free_redirection(t_redirection redirection);
void	free_token(t_token *token);
void	free_program(t_program *mini);

//init.c
void	init_struct(t_program *mini, char **env);
void	init_redirection(t_redirection *redirection);
void	init_token(t_token *token);
int		init_program(t_program *mini, char **env);

//main.c

//mini_loop.c
int		mini_loop(t_program *mini);

//utils.c
int		*save_path(t_program *mini, char **envp);

#endif