/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:12:59 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 09:45:46 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
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

t_env	*ft_find_key_env(t_env *env, char *key_value)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key_value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_abletojoin(char *str)
{
	int	plus;
	int	i;

	i = 0;
	plus = 0;
	while (str[i])
	{
		if (str[i] == '+')
			plus++;
		i++;
	}
	if (plus == 1)
		return (1);
	else if (plus > 1)
		return (2);
	return (0);
}

int	ft_key_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
