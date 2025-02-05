/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:13:22 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/03 10:39:32 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_env	*ft_find_unset(t_env *env, char *key_value)
{
	t_env	*temp;
	t_env	*prev;

	if (!ft_strcmp(env->key, key_value))
		return (env);
	prev = env;
	temp = env->next;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key_value))
			return (prev);
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}

void	ft_remove_node(t_env **env, t_env *node_exists)
{
	t_env	*temp;

	if (*env == node_exists)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->value);
		free(temp->key);
		free(temp);
	}
	else
	{
		temp = node_exists->next;
		node_exists->next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

int	ft_unset(char **cmd_array, t_env **env)
{
	t_env	*node_exists;
	int		i;

	i = 1;
	if (cmd_array[1])
	{
		while (cmd_array && cmd_array[i])
		{
			node_exists = ft_find_unset(*env, cmd_array[i]);
			if (node_exists)
				ft_remove_node(env, node_exists);
			i++;
		}
	}
	return (0);
}
