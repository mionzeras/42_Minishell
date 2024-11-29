/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:33:26 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/29 11:58:43 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_size(t_organize *program)
{
	int		i;
	t_organize	*tmp;

	i = 0;
	tmp = program;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	msg(char *msg, int check, int output)
{
	write(output, msg, ft_strlen(msg));
	if (check == 0)
		exit(1);
}

char	**ft_getenv(t_env *env)
{
	char	**ret;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp->next)
	{
		ret[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*find_path(char *cmd, char **envp, int count)
{
	char	*part_path;
	char	*cmd_path;
	char	**envp_path;

	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	envp_path = ft_split(*envp + 5, ':');
	while (envp_path[++count] && cmd[0] != '/')
	{
		part_path = ft_strjoin(envp_path[count], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free_ptr(part_path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_array(envp_path);
			return (cmd_path);
		}
		free_ptr(cmd_path);
	}
	free_array(envp_path);
	if (cmd[0] == '/' && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	msg("command not found\n", 1, 2);
	return (NULL);
}

int	exec_cmd(char *cmd, char *args, t_env *envp)
{
	char	*path;
	char	*cmd_arg;
	char	*tmp;
	char	**cmd_split;
	char	**env;

	tmp = ft_strjoin(cmd, " ");
	cmd_arg = ft_strjoin(tmp, args);
	free_ptr(tmp);
	cmd_split = ft_split(cmd_arg, ' ');
	free_ptr(cmd_arg);
	env = ft_getenv(envp);
	path = find_path(cmd, env, -1);
	if (!path)
		free_ptr(path);
	ft_printf("cmd: %s\n", cmd);
	if (execve(path, cmd_split, env) == -1)
		free_ptr(path);
	//free_ptr(path);
	free_array(cmd_split);
	return (0);
}
