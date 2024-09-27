/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:26:57 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/27 19:19:09 by gcampos-         ###   ########.fr       */
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
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
#include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define META_CHARS "<>|"
# define MINI_MSG "\e[1;93mminishell\033[91m$ \033[0m"
# define ON 0
# define OFF 1

typedef struct s_input_organize
{
	int		pipes;
	char	*input_file;
	char	*output_file;
	char	*append_file;
	char	*heredoc_delimiter;
	char	**cmd_split;
} 		t_input_organize;

//main struct
typedef struct s_program
{
	char			**env;
	char 			**path;
	char			*user_input;
	char			*pwd;
	char			*old_pwd;
	int				loop;
}		t_program;

//clean/clean.c
void	free_array(char **array);
void	free_organize(t_input_organize *program);
void	free_program(t_program *mini, t_input_organize *program);

//initialize/init.c
char	**save_path(t_program *mini, char **envp);
void	init_organize(t_input_organize *program);
void	init_struct(t_program *mini, char **env);

//loop/loop.c
int		mini_loop(t_program *mini, t_input_organize *program);

//parser/new_split.c
char	**ft_new_split(char const *s, char c);

//parser/parseline.c
int		ft_isspaces(char c);
char	*fix_redir_spaces(char *input);
int		parseline(t_program *mini);

//parser/parsing.c
void	parse_input(t_program *mini, t_input_organize *program);

//parser/quotes.c
char	*expand_variable(char *input, int *i);
int		inside_quotes(char *input, int index);

//utils/utils.c
int		is_token(char c);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif