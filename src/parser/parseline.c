/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/14 19:50:36 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_without_quotes(char *input)
{
	t_var	var;
	
	var.i = -1;
	var.size = 0;
	var.c = 0;

	while (input[++var.i])
	{
		if (input[var.i] == '\'' || input[var.i] == '\"')
		{
			var.c = input[var.i];
			var.i++;
			while (input[var.i++] && input[var.i] != var.c)
				var.size++;
			var.c = 0;
		}
		if (input[var.i] != var.c)
			var.size++;
	}
	return (var.size);
}

char	*remove_quotes(char *input)
{
	t_var	var;
	char	*new_input;

	var.i = size_without_quotes(input);
	var.j = 0;
	new_input = (char *)malloc(sizeof(char) * (var.i + 1));
	if (!new_input)
		return (NULL);
	var.i = -1;
	while (input[++var.i])
	{
		var.c = 0;
		if (input[var.i] == '\'' || input[var.i] == '\"')
		{
			var.c = input[var.i++];
			while (input[var.i] && input[var.i] != var.c)
				new_input[var.j++] = input[var.i++];
		}
		if (input[var.i] != var.c)
			new_input[var.j++] = input[var.i];
	}
	new_input[var.j] = '\0';
	free(input);
	return (new_input);
}

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
	if (ft_strnstr(str, "||", ft_strlen(str))
		|| ft_strnstr(str, "&&", ft_strlen(str)))
	{
		ft_putstr_fd("This program doesn't handle || or && \n", STDERR);
		return (true);
	}
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
	i = -1;
	j = 0;
	while (input[++i])
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
	}
	new_input[j] = '\0'; // adiciona o null no final da string
	return (new_input);
}

int	parseline(t_program *mini)
{
	char	*tmp;

	tmp = readline("minishell$ ");
	add_history(tmp);
	if (!tmp)
		exit(EXIT_SUCCESS);
	if (duplicates(tmp))
	{
		free(tmp);
		return (EXIT_FAILURE);
	}
	mini->user_input = ft_strtrim(tmp, " ");
	if (!mini->user_input)
		exit(EXIT_SUCCESS);
	free(tmp);
	tmp = fix_redir_spaces(mini->user_input);
	free(mini->user_input);
	mini->user_input = expander(tmp);
	free(tmp);
	return (EXIT_SUCCESS);
}
