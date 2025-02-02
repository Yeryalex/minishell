/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:13:22 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/02 15:19:39 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

t_env	*ft_find_unset(t_env *env, char *key_value)
{
	t_env	*temp;
	t_env	*prev;
	int		i;

	i = 0;
	prev = env;
	temp = env->next;
	while (temp)
	{
		if (!ft_strcmp(prev->key, key_value))
			return (prev);
		if (!ft_strcmp(temp->key, key_value))
			return (prev);
		prev = prev->next;
		temp = temp->next;
	}
	return (NULL);
}

void	ft_remove_node(t_env *env, t_env *node_exists)
{
	t_env	*temp;

	(void)env;
	temp = NULL;
	if (node_exists->next)
		temp = node_exists->next;
	node_exists->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}

int	ft_unset(char **cmd_array, t_env *env)
{
	t_env	*node_exists;
	int		i;

	i = 1;
	if (cmd_array[1])
	{
		while (cmd_array && cmd_array[i])
		{
			node_exists = ft_find_unset(env, cmd_array[i]);
			if (node_exists)
				ft_remove_node(env, node_exists);
			i++;
		}
	}
	return (0);
}
