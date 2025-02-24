/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:05 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/08 14:11:02 by yrodrigu         ###   ########.fr       */
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
/*
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
			return (ft_free_array(char_env), NULL);
		key_value = ft_strjoin(temp, env->value);
		if (!key_value)
			return (free(temp), ft_free_array(char_env), NULL);
		free(temp);
        *char_env = key_value;
        char_env++;
        env = env->next;
    }
	*char_env = NULL;
	return (char_env - size);
}*/
char **ft_list_to_char(t_env *env)
{
    char    **char_env;
    int     size;
    char    *key_value;
    char    *temp;
    int     i;

    size = ft_lstsize(env);
    char_env = (char **)malloc(sizeof(char *) * (size + 1));
    if (!char_env)
		return (NULL);
	i = 0;
    while (env)
    {
        temp = ft_strjoin(env->key, "=");
        if (!temp)
            return (ft_free_array(char_env), NULL);
        key_value = ft_strjoin(temp, env->value);
        free(temp);
        if (!key_value)
			return (ft_free_array(char_env), free(temp), NULL);
        char_env[i++] = key_value;
        env = env->next;
    }
    char_env[i] = NULL;
    return (char_env);
}