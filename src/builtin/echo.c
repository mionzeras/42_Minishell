/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:28:50 by caliman           #+#    #+#             */
/*   Updated: 2024/11/25 19:56:13 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função que exibe uma string na saída padrão. Com ou sem
// quebra de linha (-n).

void	print_args(char *args, int n)
{
	int		i;
	char	**str;

	printf("ENTREI args: %s\n", args);
	i = 0;
	str = ft_split(args, ' ');
	if (str[1] == NULL && n == 1)
	{
		printf("ENTREI NO IF\n");
		free_array(str);
		return ;
	}
	if (n == 1)
		i = 1;
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	free_array(str);
}

void	ft_echo(t_organize *program)
{
	int			n;
	int			i;
	char		*str;

	str = program->args;
	n = 0;
	if (program->cmds[4])
		ft_error_cmds(program);
	else if (!str)
		write(1, "\n", 1);
	else
	{
		if (str[0] == '-' && str[1] == 'n')
		{
			i = 1;
			while (str[i] == 'n')
				i++;
			if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
				n = 1;
		}
		print_args(str, n);
		if (n == 0)
			write(1, "\n", 1);
	}
}
