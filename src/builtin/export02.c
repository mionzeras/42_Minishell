/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:36:18 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/25 18:36:50 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node_with_content(char *content)
{
	t_env	*new;

	new = new_env_node();
	new->content = ft_strdup(content);
	return (new);
}
