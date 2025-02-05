/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:05 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_lstsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char **ft_list_to_char(t_env *env)
{
    char    **char_env;
    int     size;
    char    *key_value;
	char	*temp;

    size = ft_lstsize(env);
    char_env = (char **)malloc(sizeof(char *) * (size + 1));
    if (!char_env)
        return (NULL);
    while (env)
    {
        temp = ft_strjoin(env->key, "=");
       	if (!temp)
			return (NULL);
		key_value = ft_strjoin(temp, env->value);
		if (!key_value)
			return (NULL);
		free(temp);
        *char_env = key_value;
        char_env++;
        env = env->next;
    }
	*char_env = NULL;
    return (char_env - size);
}
