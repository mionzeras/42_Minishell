/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:28:12 by caliman           #+#    #+#             */
/*   Updated: 2024/11/24 16:01:15 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env(t_env *env_list, char *name, char *value, int replace)
{
	t_env *tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
		{
			if (replace)
			{
				free_ptr(tmp->content);
				tmp->content = ft_strjoin(name, value);
			}
			return ;
		}
		tmp = tmp->next;
	}
}

t_env	*ft_get_env(t_env *env_list, char *name)
{
	t_env *tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, ft_strlen(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	handle_cd_errors(char *arg)
{
    if (arg[1])
        print_error("cd: invalid argument");
    else if ((arg[0] != '-' && arg[0] != '~'))
	{
		printf("arg: %s\n", arg);
		print_error("cd: no such file or directory");
	}
}

bool	can_execute(t_env *env_list, char *arg)
{
    t_env *oldpwd = ft_get_env(env_list, "OLDPWD");
    if (arg)
    {
        if (ft_strlen(arg) == 1 && arg[0] == '-')
        {
            if (oldpwd)
            {
                printf("%s\n", oldpwd->content + 7);
                return (!chdir(oldpwd->content + 7));
            }
            else
            {
                print_error("OLDPWD not set");
                return (false);
            }
        }
        return (!chdir(arg));
    }
    t_env *home = ft_get_env(env_list, "HOME");
    if (home)
        return (!chdir(home->content + 5));
    return (false);
}

// qunado entro com o comando cd - 2 vezes ele printa a 
void	ft_cd(t_env *env_list, t_organize *program)
{
    char	dir[PATH_MAX];

    getcwd(dir, sizeof(dir));
	printf("arg size: %zu\n", ft_strlen(program->args));
    if (program->args && program->args[0] == '-' && program->args[1] != '\0')
    {
        print_error("cd: invalid option");
        return ;
    }
    if (!can_execute(env_list, program->args))
    {
        if (!program->args || ft_strcmp(program->args, "~") == 0)
        {
            handle_home_directory(env_list);
            return ;
        }
        handle_cd_errors(program->args);
        return ;
    }
    update_env_vars(env_list, dir, sizeof(dir));
}
