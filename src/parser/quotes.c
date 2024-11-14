/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:52:40 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/14 16:22:14 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_quotes(char *input, int index)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (input[++i] && i != index)
	{
		if (i > 0 && input[i - 1] == '\\')
			continue ;
		if (input[i] == '\'' && quote == 0)
			quote = 1;
		else if (input[i] == '\"' && quote == 0)
			quote = 2;
		else if ((input[i] == '\'' && quote == 1)
			|| (input[i] == '\"' && quote == 2))
			quote = 0;
	}
	return (quote);
}

char	*expand_variable(char *input, int *i)
{
	char	var_name[100];
	char	*var_value;
	int		j;
	int		k;

	j = 0;
	k = *i + 1;
	while (input[k] && (ft_isalnum(input[k])))
	{
		var_name[j++] = input[k++];
	}
	var_name[j] = '\0';
	var_value = getenv(var_name);
	*i = k - 1;
	return (var_value);
}

int	expanded_size(char *input)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (input[++i])
	{
		if (input[i] == '$' && (inside_quotes(input, i) == 0
				|| inside_quotes(input, i) == 2)
			&& (i == 0 || input[i - 1] != '\\'))
		{
			size += ft_strlen(expand_variable(input, &i));
			if (!expand_variable(input, &i))
				size++;
		}
		else
			size++;
	}
	return (size);
}

char	*expander(char *input)
{
	t_var	var;
	char	*new_str;

	var.i = -1;
	var.k = -1;
	var.size = expanded_size(input);
	new_str = malloc(var.size + 1);
	while (input[++var.i])
	{
		if (input[var.i] == '$' && (inside_quotes(input, var.i) == 0
				|| inside_quotes(input, var.i) == 2)
			&& (var.i == 0 || input[var.i - 1] != '\\'))
		{
			var.str = expand_variable(input, &var.i);
			if (!var.str)
				var.str = "$";
			var.j = -1;
			while (var.str[++var.j])
				new_str[++var.k] = var.str[var.j];
		}
		else
			new_str[++var.k] = input[var.i];
	}
	new_str[++var.k] = '\0';
	return (new_str);
}
