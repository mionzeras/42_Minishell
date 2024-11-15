/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcampos- <gcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:29:45 by gcampos-          #+#    #+#             */
/*   Updated: 2024/11/15 19:58:17 by gcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strcpy(char *src)
{
    int i;
    char *dest;

    dest = malloc(sizeof(char) * ft_strlen(src) + 1);
    i = -1;
    if (!src)
        return (NULL);
    while (src[++i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

int	pipes_counter(char *str)
{
	int i;
	int pipe;

	i = -1;
	pipe = 0;
	while (str[++i])
	{
		if (str[i] == '|' && inside_quotes(str, i) == 0)
			pipe++;
	}
	return (pipe);
}

void	update_sh_lvl(t_program *mini)
{
	int		i;
	char	*sh_lvl;
	char	*new_lvl;
	t_env	*tmp;

	i = -1;
	tmp = mini->env_list;
	while (tmp)
	{
		if (ft_strnstr(tmp->content, "SHLVL=", 6))
		{
			sh_lvl = ft_substr(tmp->content, 6, ft_strlen(tmp->content) - 6);
			new_lvl = ft_itoa(ft_atoi(sh_lvl) + 1);
			free(tmp->content);
			// free(tmp->content);
			free(sh_lvl);
			sh_lvl = ft_strjoin("SHLVL=", new_lvl);
			free(new_lvl);
			tmp->content = sh_lvl;
			// tmp->content = ft_strdup(sh_lvl);
			printf("%s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}
