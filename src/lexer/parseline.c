/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliman <caliman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/14 23:10:34 by caliman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool duplicates(char *str)
{
	char *tmp;
	int start_with_space;

	tmp = ft_strdup(str);
	start_with_space = 0;
	if (tmp[0] == ' ')
			start_with_space = 1;
	if (ft_strnstr(tmp, "||", ft_strlen(tmp)) || ft_strnstr(tmp, "&&", ft_strlen(tmp)))
	{
		ft_putstr_fd("This program doesn't handle || or && \n", STDERR);
		if (ft_strlen(tmp) > 0 && !start_with_space)
			add_history(tmp);
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

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
		if ((input[i] == '>' || input[i] == '<' || input[i] == '|')) // verifica se o char é um redirecionador e o proximo char não é um espaço
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
	char *user_input;
	int start_with_space;

	start_with_space = 0;
	user_input = readline(MINI_MSG);
	if (!user_input)
		exit(EXIT_SUCCESS);
	if (!duplicates(user_input))
	{
		char *tmp;
		
		if (user_input[0] == ' ')
			start_with_space = 1;
		tmp = ft_strtrim(user_input, " ");
		if (!tmp)
			exit(EXIT_SUCCESS);
		free(user_input);
		if (ft_strlen(tmp) > 0 && !start_with_space)
			add_history(tmp);
		mini->user_input = fix_redir_spaces(tmp);
		free(tmp);
		return (EXIT_SUCCESS);
	}
	free(user_input);
	return (EXIT_FAILURE);
}
