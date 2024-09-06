/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:52:40 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/29 19:09:05 by gcampos-         ###   ########.fr       */
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

int check_quotes(const char *input)
{
	int i;
	int single_quote;
	int double_quote;
	char *str;

	i = -1;
	str = ft_strdup(input);
	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			single_quote++;
		else if (str[i] == '\"')
			double_quote++;
	}
	if (single_quote % 2 == 0 && double_quote % 2 == 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
