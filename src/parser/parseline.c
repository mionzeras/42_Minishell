/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/08 20:48:18 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_with_spaces(char *input)
{
	char	*new_input;
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (is_token(input[i]))
			count++;
	}
	new_input = (char *)malloc(sizeof(char *) * (ft_strlen(input) + count + 1));
	if (!new_input)
		return (NULL);
	return (new_input);
}

bool	duplicates(char *str)
{
	char	*tmp;
	int		start_with_space;

	tmp = ft_strdup(str);
	start_with_space = 0;
	if (tmp[0] == ' ')
		start_with_space = 1;
	if (ft_strnstr(tmp, "||", ft_strlen(tmp))
		|| ft_strnstr(tmp, "&&", ft_strlen(tmp)))
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

int	ft_isspaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*fix_redir_spaces(char *input)
{
	char	*new_input;
	int		i;
	int		j;

	new_input = alloc_with_spaces(input);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_token(input[i]) && inside_quotes(input, i) == 0) // verifica se o char é um redirecionador e não está dentro de aspas
		{
			if (i > 0 && !ft_isspaces(input[i - 1])) // verifica se o char anterior não é um espaço
				new_input[j++] = ' '; // adiciona um espaço
			new_input[j++] = input[i];  // adiciona o redirecionador
			if ((is_token(input[i + 1])) && input[i] != '|') // verifica se o proximo char é um redirecionador e o char atual não é um pipe
				new_input[j++] = input[++i];
			if (!ft_isspaces(input[i + 1]) && input[i + 1]) // verifica se o proximo char é um espaço, caso não seja, adiciona um espaço
				new_input[j++] = ' ';
		}
		else
			new_input[j++] = input[i]; // adiciona o char normal
		i++;
	}
	new_input[j] = '\0'; // adiciona o null no final da string
	return (new_input);
}

int	parseline(t_program *mini)
{
	char	*user_input;
	char	*tmp;
	int		start_with_space;

	start_with_space = 0;
	user_input = readline(MINI_MSG);
	if (!user_input)
		exit(EXIT_SUCCESS);
	if (!duplicates(user_input))
	{
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
		mini->user_input = expander(mini->user_input);
		return (EXIT_SUCCESS);
	}
	free(user_input);
	return (EXIT_FAILURE);
}
