/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:24:31 by gcampos-          #+#    #+#             */
/*   Updated: 2024/12/01 13:48:34 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	duplicates(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|' && inside_quotes(str, i) == 0)
		{
			print_error("syntax error near unexpected token '||'", 258);//codigo de erro 258
			return (true);
		}
		if (str[i] == '&' && str[i + 1] == '&' && inside_quotes(str, i) == 0)
		{
			print_error("syntax error near unexpected token '&&'", 258); //codigo de erro 258
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

char	*fix_redir_spaces(char *str)
{
	char	*new_input;
	int		i;
	int		j;

	new_input = alloc_with_spaces(str);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (is_token(str[i]) && inside_quotes(str, i) == 0)
		{
			if (i > 0 && !ft_isspaces(str[i - 1]))
				new_input[j++] = ' ';
			new_input[j++] = str[i];
			if (((is_token(str[i + 1])) && str[i] != '|' && str[i + 1] != '|'))
				new_input[j++] = str[++i];
			if (!ft_isspaces(str[i + 1]) && str[i + 1])
				new_input[j++] = ' ';
		}
		else
			new_input[j++] = str[i];
	}
	new_input[j] = '\0';
	free_ptr(str);
	return (new_input);
}

int	parse_readline(char **input, t_env *env)
{
	char	*tmp;

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
	free_ptr(tmp);
	if (!*input)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
