/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:15:20 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/10 13:08:07 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*ft_clear_lstenv(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free (env->key);
		if (env->value)
			free (env->value);
		free (env);
		env = tmp;
	}
	return (1);
}

t_env	*ft_create_node_env(char **env)
{
	t_env	*env_node;
	

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = ft_strdup(ft_split(*env, '=')[0]);
	env_node->value = ft_strdup(ft_split(*env, '=')[1]);
	if (!env_node->value)
		env_node->exported = 0;
	else
	{
		env_node->exported = 1;
		if (*env_node->value == '+')
			env_node->value = ft_strdup(env_node->value + 2);
		else
			env_node->value = ft_strdup(env_node->value + 1);
	}
	env_node->prev = NULL;
	env_node->next = NULL;
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
		new_node->prev = tmp;
	}
}

t_env		*ft_init_env(char **env)
{
	t_env	*new_node;
	t_env	*lst_env;

	lst_env = NULL;
	while (*env)
	{
		new_node = ft_create_node_env(*env);
		if (!new_node)
		{
			ft_clear_lstenv(lst_env);
			return (NULL);
		}
		ft_add_env_tolst(&lst_env, new_node);
		env++;
	}
	return (lst_env);
}
