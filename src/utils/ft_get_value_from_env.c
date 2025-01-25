/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value_from_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:23:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/25 11:29:47 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

char    *get_value_from_env(t_env *env, char *key)
{
	while (env)
 	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);                  
}


