/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:26:57 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/25 18:43:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h> //functions: read, write, close, fork, execve, chdir, pipe, dup2, dup, waitpid, wait, wait3, wait4, signal, kill, exit	
# include <stdlib.h> //functions: malloc, free, exit, execve, getenv, realpath, system
# include <stdio.h> //functions: printf, perror, strerror
# include <sys/wait.h> //functions: waitpid, wait, wait3, wait4
# include <sys/stat.h> //functions: stat, lstat, fstat
# include <signal.h> //functions: signal, kill
# include <limits.h> //functions: PATH_MAX
# include <fcntl.h> //functions: open, close, read, write
# include <readline/readline.h> //functions: readline, add_history
# include <readline/history.h> //functions: using_history
# include <stdbool.h> //types: bool
# include <errno.h> //variables: errno
# include "libft.h" //libft functions

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ENV 0
# define META_CHARS "<>|"
# define ON 0
# define OFF 1

# define PATH_MAX 4096
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define ERROR_PWD_ARGUMENTS "pwd: too many arguments"
# define ERROR_PWD_DIRECTORY "pwd: couldn't get current directory"
# define ERROR_CD_ARGS "cd: too many arguments"
# define ERROR_CD_HOME "cd: HOME not set"
# define ERROR_CD_OLDPWD "cd: OLDPWD not set"
# define ERROR_CD_DIRECTORY "cd: no such file or directory"
# define ERROR_EXIT_ARGS "exit: too many arguments"	
# define ERROR_EXIT_DIGIT "exit: numeric argument required"

extern int	g_exit_status;

typedef struct s_var
{
	int		i;
	int 	j;
	int		k;
	int		inside;
	int		size;
	char 	c;
	char 	*str;
} t_var;

typedef struct s_organize
{
	int					fd_in;
	int					fd_out;
	int					list_pos;
	char				*input_file;
	char				*output_file;
	char				*append_file;
	char				*heredoc_dlm;
	char				*cmds;
	char				*args;
	struct s_organize	*next;
}		t_organize;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}		t_env;

//main struct
typedef struct s_program
{
	int				pipes;
	int				loop;
	char			**path;
	char			*user_input;
	char			*pwd;
	char			*old_pwd;
	struct s_env	*env_list;
	struct s_env	*export_list;
}		t_program;

//builtin/cd00.c
void		ft_cd(t_env *env_list, t_organize *program);
t_env		*ft_get_env(t_env *env_list, char *name);
void		ft_update_env(t_env *env_list, char *name, char *value, int replace);

//builtin/cd01.c
void		update_env_vars(t_env *env_list, char *dir, int size);
void		handle_home_directory(t_env *env_list);

//builtin/echo.c
void		ft_echo(t_organize *program);

//builtin/env.c
void		add_env_node(t_env *node, t_env *new);
t_env		*new_env_node(void);
t_env		*init_env(char **env);
void		ft_env(t_env *env_list, t_organize *program);
void		print_env_list(t_env *list);

//builtin/export.c
void		ft_export(t_env *env_list, char *input);

//builtin/exit.c
void		free_and_exit(t_organize *pgr, int status);
int			check_exit_args(char **args);
int			ft_exit(t_organize *program, char *str);

//builtin/pwd.c
void		ft_pwd(t_organize *program);

//builtin/unset.c
void		ft_unset(t_env *env_list, t_organize *program);

//clean/clean.c
void		delete_node(t_env *node);
void		delete_list(t_env *list);
void		free_array(char **array);
void		free_organize(t_organize *program);
void		free_program(t_program *mini); //old -> free_program(t_program *mini, t_organize *program);
int			size_without_quotes(char *input);

//env/env.c
void		add_env_node(t_env *node, t_env *new);
t_env		*new_env_node(void);
t_env		*init_env(char **env);

//error/error.c
void		print_error(char *cmd);
void		ft_error_cmds(t_organize *program);
void		ft_error_args(char *str);

//exec/execution.c
void		ft_exec_builtin(t_organize *program, t_program *mini);
int			is_builtin(char *command);
void		redir_pipes(t_organize *program);
void		executor(t_organize *program, t_program *mini);

//exec/exec_utils.c
int			exec_cmd(char *cmd, char *args, t_env *envp);

//initialize/init.c
void		print_list(t_organize *program);
void		save_path(t_program *mini, char **envp);
t_organize	*init_organize(char *input);
void		init_struct(t_program *mini, char **env);

//loop/loop.c
int	mini_loop(t_program *mini, int fd1, int fd2); // old -> int mini_loop(t_program *mini, t_organize *program);

//parser/new_split.c
char		**ft_new_split(char *s, char c);

//parser/parseline.c
int			size_without_quotes(char *input);
char		*remove_quotes(char *input);
int			ft_isspaces(char c);
char		*fix_redir_spaces(char *input);
int			parse_readline(char **input, t_env *env);

//parser/parsing.c
int			parse_organize(t_organize *program, char *str);
int			process_input(t_organize *program, char **str);

//parser/quotes.c
int			inside_quotes(char *input, int index);
char		*expand_variable(char *input, int *i, t_env *env);
char		*expander(char *input, t_env *env);

//utils/utils.c
void		free_ptr(char *ptr);
int			is_token(char c);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//utils/utils2.c
char		*ft_strcpy(char *src);
int			pipes_counter(char *str);
void		update_sh_lvl(t_env *env);
#endif