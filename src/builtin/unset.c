/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:35:08 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/20 21:51:06 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Esta função é responsável por remover uma variável de ambiente da
// lista encadeada de variáveis de ambiente:
// 1. Verifica se o número de argumentos é diferente de 2.
// 2. Encontra o nó da variável de ambiente a ser removida.
// 3. Se o nó não for encontrado, exibe uma mensagem de erro.
// 4. Remove o nó da lista encadeada.
// 5. Libera a memória associada ao nó removido.
// 6. "unset with NO OPTIONS"

void	remove_env_var(t_program *mini, char *var)
{
    t_env	*node;

    node = mini->env_list;
    while (node)
    {
        if (ft_strncmp(node->content, var, ft_strlen(var)) == 0)
        {
            if (node->prev)
                node->prev->next = node->next;
            if (node->next)
                node->next->prev = node->prev;
            if (node == mini->env_list)
                mini->env_list = node->next;
            free_ptr(node->content);
            free(node);
            break ;
        }
        node = node->next;
        // if (var)
        // {
        //     free(var);
        //     var = NULL;
        // }
    }
}

void	ft_unset(t_program *mini, t_organize *program)
{
    int		i;
    char	**cmd_args;

    if (program->cmds[5])
        ft_error_cmds(program);
    else if (!program->args)
        ft_error_args();
    else
    {
        cmd_args = ft_split(program->args, ' ');
        i = 0;
        while (cmd_args[i])
        {
            remove_env_var(mini, cmd_args[i]);
            i++;
        }
        if (cmd_args)
        {
            free_array(cmd_args);
            cmd_args = NULL;
        }
    }
}