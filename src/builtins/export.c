/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:57 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/28 12:52:22 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_lstsize(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*ft_copy_envlst(t_env *env)
{
	t_env *new_env;
	int	size_env;

	size_env = ft_lstsize(env);
	new_env = (t_env *)malloc(sizeof(t_env) * size_env);
	while (env)
	{
		new_env->key = env->key;
		new_env->value = env->value;
		new_env = new_env->next;
		env = env->next;
	}
	new_env->next = NULL;
	return (new_env);
}

int	ft_export(t_env *env)
{
	t_env *env_copy;

	env_copy = ft_copy_envlst(env);
	while (env_copy)
	{
		printf("%s\n", env_copy->key);
		env_copy = env_copy->next;
	}
	return (0);
}
