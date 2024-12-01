/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd01.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:00:55 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/26 16:24:45 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_vars(t_env *env_list, char *dir, int size)
{
	ft_update_env(env_list, "OLDPWD=", dir, 1);
	getcwd(dir, size);
	ft_update_env(env_list, "PWD=", dir, 1);
}

void	handle_home_directory(t_env *env_list)
{
	t_env	*home;

	home = ft_get_env(env_list, "HOME");
	if (home)
		chdir(home->content + 5);
	else
		print_error("HOME not set");
}
