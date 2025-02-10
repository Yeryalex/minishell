/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:15:20 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/10 12:54:55 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_clear_lstenv(t_env *envs)
{
	t_env	*tmp;

	while (envs)
	{
		tmp = envs->next;
		free (envs->key);
		free (envs->value);
		free (envs);
		envs = tmp;
	}
	return (0);
}

t_env	*ft_create_node_env(char *envs)
{
	t_env	*env_node;
	
	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_get_env_key(envs);
	if (!env_node->key)
		return (free(env_node), NULL);
	env_node->value = ft_get_env_value(envs);
	if (!env_node->value || !env_node->key)
	{
		env_node->exported = 0;
		return(free(env_node->key), free(env_node), NULL);
	}
	else
	{
		env_node->exported = 1;
		if (*env_node->value == '+')
			env_node->value = ft_strdup(env_node->value + 2);
		else
			env_node->value = ft_strdup(env_node->value + 1);
	}
	if (!env_node->value)
		return (free(env_node->key), free(env_node), NULL);
	env_node->next = NULL;
	//printf("%s, %p\n", env_node->key, env_node);
	return (env_node);
}

void	ft_add_env_tolst(t_env **lst_env, t_env *new_node)
{
	t_env	*tmp;

	tmp = NULL;
	if (!new_node)
		return ;
	if (!*lst_env)
		*lst_env = new_node;
	else
	{
		tmp = *lst_env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		//new_node->prev = tmp;
	}
}

t_env		*ft_init_env(char **envs)
{
	t_env	*new_node;
	t_env	*lst_env;

	lst_env = NULL;
	new_node = NULL;
	while (*envs)
	{
		new_node = ft_create_node_env(*envs);
		if (!new_node)
		{
			ft_clear_lstenv(lst_env);
			ft_clear_lstenv(new_node);
			return (NULL);
		}
		ft_add_env_tolst(&lst_env, new_node);
		envs++;
	}
	return (lst_env);
}
