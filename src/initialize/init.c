/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:30:46 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/21 21:55:05 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_organize *program)
{
	t_organize	*tmp;
	int			i;

	i = 0;
	tmp = program;
	while (tmp)
	{
		printf("Node %d:\n", i);
		printf("Node address: %p\n", (void*)tmp);
		printf("input_file: %s\n", tmp->input_file);
		printf("output_file: %s\n", tmp->output_file);
		printf("append_file: %s\n", tmp->append_file);
		printf("heredoc_dlm: %s\n", tmp->heredoc_dlm);
		printf("cmds: %s\n", tmp->cmds);
		printf("args: %s\n", tmp->args);
		printf("next: %p\n", (void*)tmp->next);
		tmp = tmp->next;
		i++;
	}
}

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
	new->fd_in = -1;
	new->fd_out = -1;
	new->list_pos = 0;
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
		free_ptr(mini->path[i]);
		mini->path[i] = tmp;
	}
}

t_organize	*init_organize(char *input)
{
	int			i;
	int			pipes;
	t_organize	*list;

	i = -1;
	pipes = pipes_counter(input);
	while (++i <= pipes)
	{
		if (i == 0)
			list = new_node();
		else
			add_node(list, new_node());
	}
	return (list);
}

void	init_struct(t_program *mini, char **env)
{
	mini->pipes = 0;
	mini->loop = ON;
	save_path(mini, env);
	mini->user_input = NULL;
	mini->pwd = getcwd(0, 0);
	mini->old_pwd = NULL;
	mini->env_list = init_env(env);
	mini->export_list = init_env(env);
	update_sh_lvl(mini->env_list);
	update_sh_lvl(mini->export_list);
}
