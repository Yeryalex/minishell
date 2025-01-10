/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:31:54 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/10 12:11:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*t_env    *ft_env_init(char **env)
{
    t_env	*env_list;
    t_env	*new;
    int		i;

    i = 0;
    env_list = NULL;
    while (env[i])
    {
        new = (t_env *)malloc(sizeof(t_env));
        if (!new)
        {
            free(new);
            return (NULL);
        }
        new->key = ft_strdup(ft_split(*env, '=')[0]);
        new->value = ft_strdup(ft_split(*env, '=')[1]);
        new->next = env_list;
        env_list = new;
        i++;
    }

    return (env_list);
}*/
