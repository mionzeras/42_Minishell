/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:10:50 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/26 00:31:46 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

char	*generate_filename(int h)
{
	char	*h_str;
	char	*filename;

	h_str = ft_itoa(h);
	filename = ft_strjoin(h_str, ".tmp");
	free_ptr(h_str);
	return (filename);
}

void	process_line(int fd, char *line, int expand, t_env *env)
{
	char	*expanded;

	if (expand)
	{
		expanded = expander(line, env);
		write(fd, expanded, ft_strlen(expanded));
		free_ptr(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	heredoc(char *input, t_env *env)
{
	t_var		var;
	char		*line;
	char		*tmp;
	char		*filename;
	static int	h;

	var.k = (input[0] == '\'' || input[0] == '\"');
	h++;
	tmp = ft_strdup(input);
	tmp = remove_quotes(tmp);
	filename = generate_filename(h);
	var.i = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.i < 0)
		return (free_ptr(tmp), free_ptr(filename), perror("Error opening file"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, tmp) == 0)
			break;
		process_line(var.i, line, !var.k, env);
	}
	free_ptr(line);
	free_ptr(tmp);
	free_ptr(filename);
	return (var.i);
}

// int heredoc(char *input, t_env *env)
// {
//     t_var       var;
//     char        *line;
//     char        *tmp;
//     char        *filename;
//     static int  h; // Mantém o valor entre chamadas da função

//     var.i = 0;
//     var.k = 0;

//     if (input[0] == '\'' || input[0] == '\"')
//         var.k = 1;

//     if (input)
//     {
//         h++; // Incrementa o contador para o arquivo
//         tmp = ft_strdup(input);
//         tmp = remove_quotes(tmp);
        
//         // Gera o nome do arquivo
//         char *h_str = ft_itoa(h); // Converte o número para string
//         filename = ft_strjoin(h_str, ".tmp");
//         free_ptr(h_str);

//         printf("filename: %s\n", filename);

//         // Abre o arquivo para escrita
//         var.i = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
//         if (var.i < 0) // Verifica erro ao abrir arquivo
//         {
//             perror("Error opening heredoc file");
//             free_ptr(tmp);
//             free_ptr(filename);
//             return (-1);
//         }

//         // Loop para processar o conteúdo do heredoc
//         while (1)
//         {
//             line = readline("> ");
//             if (!line) // EOF ou Ctrl+D
//                 break;
//             if (ft_strcmp(line, tmp) == 0) // Se o delimitador for encontrado
//                 break;
//             if (!var.k)
//             {
//                 var.str = expander(line, env); // Expande variáveis
//                 write(var.i, var.str, ft_strlen(var.str));
//                 free_ptr(var.str);
//             }
//             else
//                 write(var.i, line, ft_strlen(line)); // Sem expansão
//             write(var.i, "\n", 1);
//             free_ptr(line);
//         }

//         // Libera recursos
//         free_ptr(line);
//         free_ptr(tmp);
//         free_ptr(filename);
//     }
//     return (var.i);
// }


// int	heredoc(char *input, t_env *env)
// {
// 	t_var		var;
// 	char		*line;
// 	char		*tmp;
// 	char		*filename;
// 	static int	h;

// 	var.i = 0;
// 	var.k = 0;
// 	h = 0;
// 	if (input[0] == '\'' || input[0] == '\"')
// 		var.k = 1;
// 	if (input)
// 	{
// 		h++;
// 		tmp = ft_strdup(input);
// 		tmp = remove_quotes(tmp);
// 		filename = ft_strjoin(ft_itoa(h), ".tmp");
// 		printf("filename: %s\n", filename);
// 		var.i = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);	
// 		while (1)
// 		{
// 			line = readline("> ");
// 			if (!line)
// 				break;
// 			if (ft_strcmp(line, tmp) == 0)
// 				break;
// 			if (!var.k)
// 			{
// 				var.str = expander(line, env);
// 				write(var.i, var.str, ft_strlen(var.str));
// 				free_ptr(var.str);
// 			}
// 			else
// 				write(var.i, line, ft_strlen(line));
// 			write(var.i, "\n", 1);
// 		}
// 		free_ptr(filename);
// 		free_ptr(line);
// 		free_ptr(tmp);
// 	}
// 	return (var.i);
// }
