/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:20:36 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/27 18:20:48 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_redirection(char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<<") == 0);
}

char *organize_input(const char *input)
{
	char **tokens = ft_split(input, ' ');  // Função split personalizada
	t_input_organize program = {NULL, NULL, NULL, NULL, NULL};
	char *result;
	int i = -1;

	// Alocar um buffer grande o suficiente para o resultado reorganizado
	result = malloc(strlen(input) * 2 + 1);
	if (!result)
		return NULL;
	result[0] = '\0';
	// Percorre os tokens do input
	while (tokens[++i])
	{
		if (strcmp(tokens[i], "<") == 0 && tokens[i + 1])
			program.input_file = tokens[++i];  // Arquivo de entrada após '<'
		else if (strcmp(tokens[i], "<<") == 0 && tokens[i + 1])
			program.heredoc_delimiter = tokens[++i];  // Delimitador heredoc após '<<'
		else if (strcmp(tokens[i], ">") == 0 && tokens[i + 1])
			program.output_file = tokens[++i];  // Arquivo de saída após '>'
		else if (strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
			program.append_file = tokens[++i];  // Arquivo de saída (append) após '>>'
		else
		{
			// Comandos e argumentos
			if (program.cmds == NULL)
				program.cmds = strdup(tokens[i]);  // Inicializa os comandos
			else
			{
				program.cmds = realloc(program.cmds, strlen(program.cmds) + strlen(tokens[i]) + 2);  // Realoca para mais comandos
				strcat(program.cmds, " "); // Adiciona espaço entre comandos
				strcat(program.cmds, tokens[i]); // Adiciona o comando
			}
		}
	}
	// Montar a string final na ordem correta
	if (program.heredoc_delimiter)
	{
		strcat(result, "<< ");
		strcat(result, program.heredoc_delimiter);
		strcat(result, " ");
	}
	if (program.input_file)
	{
		strcat(result, "< ");
		strcat(result, program.input_file);
		strcat(result, " ");
	}
	if (program.cmds)
	{
		strcat(result, program.cmds);
		strcat(result, " ");
	}
	if (program.output_file)
	{
		strcat(result, "> ");
		strcat(result, program.output_file);
		strcat(result, " ");
	}
	if (program.append_file)
	{
		strcat(result, ">> ");
		strcat(result, program.append_file);
		strcat(result, " ");
	}
	// Liberar tokens e memória temporária
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	if (program.cmds)
		free(program.cmds);

	return result;
}


char *expand_variable(char *input, int *i)
{
	char var_name[100];
	char *var_value;
	int j = 0;
	int k = *i + 1;

	while (input[k] && (ft_isalnum(input[k])))
	{
		var_name[j++] = input[k++];
	}
	var_name[j] = '\0';
	var_value = getenv(var_name);
	*i = k;
	return (var_value);
}
