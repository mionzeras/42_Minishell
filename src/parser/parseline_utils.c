/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:35:08 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/26 16:47:26 by gcampos-         ###   ########.fr       */
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
