/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:52:40 by gcampos-          #+#    #+#             */
/*   Updated: 2024/09/27 17:53:35 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

int inside_quotes(char *input, int index)
{
	int i;
	int quote;

	i = -1;
	quote = 0;
	while (input[++i] && i != index)
	{
		if (i > 0 && input[i - 1] == '\\')
			continue;
		if (input[i] == '\'' && quote == 0)
			quote = 1;
		else if (input[i] == '\"' && quote == 0)
			quote = 2;
		else if ((input[i] == '\'' && quote == 1) || (input[i] == '\"' && quote == 2))
			quote = 0;
	}
	return (quote);
}
