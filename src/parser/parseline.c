/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/25 17:43:20 by gcampos-         ###   ########.fr       */
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
	free_ptr(input);
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
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|' && inside_quotes(str, i) == 0)
		{
			ft_printf("minishell: syntax error near unexpected token `||'\n");
			return (true);
		}
		if (str[i] == '&' && str[i + 1] == '&' && inside_quotes(str, i) == 0)
		{
			ft_printf("minishell: syntax error near unexpected token `&&'\n");
			return (true);
		}
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
			if (((is_token(input[i + 1])) && input[i] != '|' && input[i + 1] != '|')) // verifica se o proximo char é um redirecionador e o char atual não é um pipe
				new_input[j++] = input[++i];
			if (!ft_isspaces(input[i + 1]) && input[i + 1]) // verifica se o proximo char é um espaço, caso não seja, adiciona um espaço
				new_input[j++] = ' ';
		}
		else
			new_input[j++] = input[i]; // adiciona o char normal
	}
	new_input[j] = '\0'; // adiciona o null no final da string
	free_ptr(input); // libera a string original
	return (new_input);
}

int	parse_readline(char **input, t_env *env)
{
	char	*tmp;
	
	ft_printf("entrei no parseline\n");
	if (*input && input[0])
		add_history(*input);
	if (!*input)
		exit(EXIT_SUCCESS);
	if (duplicates(*input))
		return (EXIT_FAILURE);
	tmp = ft_strtrim(*input, " ");
	if (!tmp)
		return (EXIT_FAILURE);
	free_ptr(*input);
	tmp = fix_redir_spaces(tmp);
	*input = expander(tmp, env);
	ft_printf("sai do expander\n");
	free_ptr(tmp);
	if (!*input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
