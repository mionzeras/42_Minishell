/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:21:39 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/12 20:38:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void    heredoc(t_organize *prog)
{
    t_organize   *tmp;
    char        *line;
    int         fd;

    tmp = prog;
    while (tmp)
    {
        fd = 0;
        if (tmp->heredoc_dlm != NULL)
        {
            fd = open("test.txt", O_RDONLY, O_WRONLY, O_TRUNC);
            while (1)
            {
                line = readline(">");
                if (ft_strcmp(line, tmp->heredoc_dlm) == 0)
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, '\n', 2);
                free (line);
            }
            tmp->fd_in = fd;
        }
        tmp = tmp->next;
    }
}
