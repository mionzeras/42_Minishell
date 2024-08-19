/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:09:17 by gcampos-          #+#    #+#             */
/*   Updated: 2024/08/18 21:50:13 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(void)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
}

void ft_echo(char **line)
{
	int i;
	
	i = 1;
	while (line[i])
	{
		ft_printf("%s", line[i]);
		if (line[i + 1])
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
}

void ft_cd(char **line)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (line[1] == NULL)
	{
		chdir(getenv("HOME"));
	}
	else if (ft_strncmp(line[1], "~", 1) == 0)
	{
		chdir(getenv("HOME"));
	}
	else if (ft_strncmp(line[1], "-", 1) == 0)
	{
		chdir(getenv("OLDPWD"));
	}
	else
	{
		if (chdir(line[1]) == -1)
			ft_printf("cd: %s: No such file or directory\n", line[1]);
	}
	free(cwd);
}

