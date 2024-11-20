/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliman <caliman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:28:12 by caliman           #+#    #+#             */
/*   Updated: 2024/11/16 23:16:36 by caliman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_home(t_env *env_list)
{
    t_env	*tmp;

    tmp = env_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->content, "HOME=", 5) == 0)
        {
            if (chdir(tmp->content + 5) == -1)
                print_error("cd");
            break ;
        }
        tmp = tmp->next;
    }
}

void	ft_cd_oldpwd(t_env *env_list)
{
    t_env	*tmp;

    tmp = env_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->content, "OLDPWD=", 7) == 0)
        {
            if (chdir(tmp->content + 7) == -1)
                print_error("cd");
            break ;
        }
        tmp = tmp->next;
    }
}

void	ft_cd_path(char *path)
{
    if (chdir(path) == -1)
        print_error("cd");
}

void	ft_cd(t_program *mini, t_organize *program)
{
    if (program->args == NULL)
        ft_cd_home(mini->env_list);
    else if (ft_strncmp(program->args, "~", 1) == 0)
        ft_cd_home(mini->env_list);
    else if (ft_strncmp(program->args, "-", 1) == 0)
        ft_cd_oldpwd(mini->env_list);
    else
        ft_cd_path(program->args);
}
