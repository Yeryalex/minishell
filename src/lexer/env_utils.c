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

char	**ft_list_to_char(t_env *env)
{
	char	**char_env;
	int		size;
	char	*key_value;

	size = ft_lstsize(env);
	char_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!char_env)
		return (NULL);
	for (int i = 0; env; i++, env = env->next)
	{
		key_value = ft_strjoin(env->key, "=");
		char_env[i] = ft_strjoin(key_value, env->value);
		free(key_value);
		if (!char_env[i])
		{
			ft_free_array(char_env);
			return (NULL);
		}
	}
	char_env[size] = NULL;
	return (char_env);
}
