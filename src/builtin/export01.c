/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:34:31 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/25 18:35:05 by fgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_array(char **env_array, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	count_env_list(t_env *env_list)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**create_env_array(t_env *env_list, int count)
{
	char	**env_array;
	t_env	*tmp;
	int		i;

	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
	{
		free(env_array);
		return (NULL);
	}
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		env_array[i++] = ft_strdup(tmp->content);
		if (!env_array[i - 1])
		{
			free_array(env_array);
			return (NULL);
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	print_env_array(char **env_array)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (env_array[i])
	{
		equal_sign = ft_strchr(env_array[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			ft_printf("declare -x %s=\"%s\"\n", env_array[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
		{
			ft_printf("declare -x %s\n", env_array[i]);
		}
		i++;
	}
}

void	print_sorted_env_list(t_env *env_list)
{
	int		count;
	char	**env_array;

	count = count_env_list(env_list);
	env_array = create_env_array(env_list, count);
	if (!env_array)
		return ;

	sort_env_array(env_array, count);
	print_env_array(env_array);
	if (env_array)
	{
		free_array(env_array);
		env_array = NULL;
	}
}
