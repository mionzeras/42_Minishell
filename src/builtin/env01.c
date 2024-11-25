/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliman <caliman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:38:04 by caliman           #+#    #+#             */
/*   Updated: 2024/11/12 23:38:07 by caliman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Função q lista todas as variáveis de ambiente.
/*
void ft_env(t_program *pgr)
{
	t_envp *envp;

	envp = pgr->envp;
	while (envp)
	{
		if (envp->value)
		{
			ft_putstr_fd(envp->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(envp->value, STDOUT_FILENO);
		}
		else
		{
			print_error(ERROR_ENV_DIRECTORY);
		}
		envp = envp->next;
	}
}
*/

// Função para adicionar um nó de variável de ambiente ao final
// da lista encadeada.
t_envp *add_envp_node(t_envp *new, t_envp *envp)
{
	t_envp *temp;
	
	if (!envp)
		return (new);
	temp = envp;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (envp);
}

// Função para criar um novo nó de variável de ambiente.
t_envp *new_envp_node(char *name, char *value)
{
	t_envp *envp;
	
	envp = (t_envp *)malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);
	envp->name = ft_strdup(name);
	envp->value = ft_strdup(value);
	envp->full = NULL;
	envp->visible = NULL;
	envp->next = NULL;
	return (envp);
}

// Função para encontrar um nó de variável de ambiente pelo nome.
t_envp *find_envp_node(char *name, t_envp *envp)
{
	t_envp *temp;
	
	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/*
A função remove_envp_node percorre a lista de de ambiente para
encontrar e remover um nó específico. Ela atualiza os ponteiros
da lista e libera a memória associada ao nó removido.
*/
void remove_envp_node(t_envp **envp, t_envp *node_to_remove)
{
	t_envp *temp;
	t_envp *prev;

	temp = *envp;
	prev = NULL;
	while (temp)
	{
		if (temp == node_to_remove)
		{
			if (prev)
				prev->next = temp->next;
			else
				*envp = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}