/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/11 19:45:49 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return 1;
	return 0;
}


char *fix_redir_spaces(const char *input)
{
	char *new_input;
	int i;
	int j;

	new_input = malloc(ft_strlen(input) * 2 + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<'))
		{
			if (i > 0 && !ft_isspaces(input[i-1])) // verifica se o char anterior é um espaço, caso não seja, adiciona um espaço
				new_input[j++] = ' ';
			new_input[j++] = input[i];
			if (input[i + 1] == '>' || input[i + 1] == '<') // verifica se o proximo char é um redirecionador
				new_input[j++] = input[++i];
			if (!ft_isspaces(input[i + 1]) && input[i + 1]) // verifica se o proximo char é um espaço, caso não seja, adiciona um espaço
				new_input[j++] = ' ';
		}
		else
			new_input[j++] = input[i]; // adiciona o char normal
		i++;
	}
	new_input[j] = '\0'; // adiciona o null no final da string
	return new_input;
}

int parseline(t_program *mini)
{
	char *tmp;
	char *user_input;
	int start_with_space;

	start_with_space = 0;
	user_input = readline(MINI_MSG);
	if (!user_input)
		exit(EXIT_SUCCESS);
	if (user_input[0] == ' ')
		start_with_space = 1;
	tmp = ft_strtrim(user_input, " ");
	free(user_input);
	if (!tmp)
		exit(EXIT_SUCCESS);
	if (ft_strlen(tmp) > 0 && !start_with_space)
		add_history(tmp);
	if (mini->user_input)
		free(mini->user_input);	
	mini->user_input = fix_redir_spaces(tmp);
	free(tmp);
	return (EXIT_SUCCESS);
}
