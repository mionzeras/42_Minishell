/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/09 17:16:11 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node(t_organize *node, t_organize *new)
{
	t_organize	*last;

	if (!new)
		return ;
	if (!node)
		node = new;
	else
	{
		last = node;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_organize	*new_node(void)
{
	t_organize *new;

	new = malloc(sizeof(t_organize));
	if (!new)
		return (NULL);
	new->append_file = NULL;
	new->args = NULL;
	new->cmds = NULL;
	new->heredoc_dlm = NULL;
	new->input_file = NULL;
	new->output_file = NULL;
	new->next = NULL;
	return (new);
}

void	save_path(t_program *mini, char **envp)
{
	int			i;
	char		*tmp;

	i = -1;
	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	mini->path = ft_split(*envp + 5, ':');
	while (mini->path[++i])
	{
		tmp = ft_strjoin(mini->path[i], "/");
		free (mini->path[i]);
		mini->path[i] = tmp;
	}
}

void	init_organize(t_organize *program, t_program *mini)
{
	int			i;
	t_organize	*list;

	i = -1;
	pipes_counter(mini);
	while (++i <= mini->pipes)
	{
		if (i == 0)
			list = new_node();
		else
			add_node(list, new_node());
	}
	*program = *list;
}

void	init_struct(t_program *mini, char **env)
{
	mini->pipes = 0;
	mini->loop = ON;
	mini->env = env;
	save_path(mini, env);
	mini->user_input = NULL;
	mini->pwd = getcwd(0, 0);
	mini->old_pwd = NULL;
	//update_sh_lvl(mini);
}
