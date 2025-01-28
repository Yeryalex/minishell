/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:57 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/28 20:03:47 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

void	ft_sort_env(t_env *env)
{
	t_env	*front;
	char	*temp_key;
	char	*temp_value;

	while (env)
	{
		front = env->next;
		while (front)
		{
			if (ft_strcmp(env->key, front->key) > 0)
			{
				temp_key = env->key;
				env->key = front->key;
				front->key = temp_key;

				temp_value = env->value;
				env->value = front->value;
				front->value = temp_value;
			}
			front = front->next;
		}
		env = env->next;
	}
}

t_env	*ft_copy_envlst(t_env *env)
{
	t_env *new_node;
	t_env *new_env = NULL;
	t_env *current = NULL;
	
	while (env)
	{
		new_node = (t_env * )malloc(sizeof(t_env));
		if(!new_node)
			return (NULL);
		new_node->key = ft_strdup(env->key);
		new_node->value = ft_strdup(env->value);
		new_node->next = NULL;

		if (!new_env)
			new_env = new_node;
		else
			current->next = new_node;
		current = new_node;
		env = env->next;
	}
	return (new_env);
}

int	ft_export(t_cmds *cmd, t_env *env)
{
	t_env *env_copy;
	(void)cmd;
	printf("This is the argument of export = %s\n", cmd->cmd_array[1]);
	env_copy = ft_copy_envlst(env);
	ft_sort_env(env_copy);
	while (env_copy)
	{
		printf("%s", env_copy->key);
		printf("=%s\n", env_copy->value);
		env_copy = env_copy->next;
	}
	return (0);
}
