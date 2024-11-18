/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:41 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/18 16:25:10 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	handle_redir(t_organize *organize)
{
	t_organize	*tmp;
	int			fd[2];

	tmp = organize;
	while (tmp)
	{
		if (tmp->input_file)
		{
			fd[0] = open(tmp->input_file, O_RDONLY);
			if (fd[0] < 0)
			{
				ft_printf("minishell: %s: %s\n", tmp->input_file, strerror(errno));
				return ;
			}
			dup2(fd[0], STDIN);
			close(fd[0]);
		}
		if (tmp->output_file)
		{
			fd[1] = open(tmp->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd[1] < 0)
			{
				ft_printf("minishell: %s: %s\n", tmp->output_file, strerror(errno));
				return ;
			}
			dup2(fd[1], STDOUT);
			close(fd[1]);
		}
		if (tmp->append_file)
		{
			fd[1] = open(tmp->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd[1] < 0)
			{
				ft_printf("minishell: %s: %s\n", tmp->append_file, strerror(errno));
				return ;
			}
			dup2(fd[1], STDOUT);
			close(fd[1]);
		}
		if (tmp->heredoc_dlm)
		{
			//heredoc(tmp->heredoc_dlm);
		}
		tmp = tmp->next;
	}
}