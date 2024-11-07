/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:52:40 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/07 19:21:46 by gcampos-         ###   ########.fr       */
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
			|| inside_quotes(input, i) == 2) && (i == 0 || input[i - 1] != '\\'))
		{
			size += ft_strlen(expand_variable(input, &i));
		}
		else
			size++;
	}
	return (size);
}

char	*expander(char *input)
{
	int		i;
	int 	j;
	int		k;
	int		new_len;
	char	*env_value;
	char 	*new_str;

	i = -1;
	j = -1;
	k = -1;
	new_len = expanded_size(input);
	new_str = malloc(new_len + 1);
	while (input[++i])
	{
		if (input[i] == '$' && (inside_quotes(input, i) == 0
			|| inside_quotes(input, i) == 2) && (i == 0 || input[i - 1] != '\\'))
		{
			env_value = expand_variable(input, &i);
			if (!env_value)
				continue ;
			while (env_value[++j])
				new_str[++k] = env_value[j];
		}
		else
			new_str[++k] = input[i];
	}
	new_str[++k] = '\0';
	free(input);
	return (new_str);
}
