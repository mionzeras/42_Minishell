/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomes-c <fgomes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:32:32 by fgomes-c          #+#    #+#             */
/*   Updated: 2024/11/20 21:33:54 by fgomes-c         ###   ########.fr       */
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
        return (NULL);

    i = 0;
    tmp = env_list;
    while (tmp)
    {
        env_array[i++] = tmp->content;
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

int	get_var_len(char *var)
{
    char	*equal_sign;
    int		var_len;

    equal_sign = ft_strchr(var, '=');
    if (equal_sign)
        var_len = equal_sign - var;
    else
        var_len = ft_strlen(var);
    return (var_len);
}

void	update_env_node(t_env *tmp, char *var)
{
    free_ptr(tmp->content);
    tmp->content = var;
}

void	update_or_add_env_node(t_env **env_list, char *var, int replace)
{
    t_env	*tmp;
    int		var_len;

    var_len = get_var_len(var);
    tmp = *env_list;
    while (tmp)
    {
        if (ft_strncmp(tmp->content, var, var_len) == 0 && (tmp->content[var_len] == '=' || tmp->content[var_len] == '\0'))
        {
            if (replace)
                update_env_node(tmp, var);
            return;
        }
        tmp = tmp->next;
    }
    add_env_node(*env_list, new_env_node_with_content(var));
}

void	handle_export_args(t_program *mini, char **args)
{
    int		i;
    char	*var;
    int		replace;

    i = 1;
    while (args[i])
    {
        var = ft_strdup(args[i]);
        replace = ft_strchr(var, '=') != NULL;
        update_or_add_env_node(&(mini->export_list), var, replace);
        if (replace)
            update_or_add_env_node(&(mini->env_list), var, replace);
        free_ptr(var);
        i++;
    }
}

void	ft_export(t_program *mini)
{
    char	**args;

    args = ft_split(mini->user_input, ' ');
    if (args[1] == NULL)
    {
        print_sorted_env_list(mini->export_list);
        if (args)
        {
            free_array(args);
            args = NULL;
        }
        return ;
    }
    handle_export_args(mini, args);
    if (args)
    {
        free_array(args);
        args = NULL;
    }
}