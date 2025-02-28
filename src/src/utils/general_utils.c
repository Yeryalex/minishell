/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:07:56 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 20:45:02 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_valid_export(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] == '_' || str[i] == '+'
					|| (str[i] >= 'A' && str[i] <= 'Z')
					|| (str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= '0' && str[i] <= '9'))))
			counter++;
		i++;
	}
	return (counter);
}

int	ft_valid_env(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

void	ft_modify_especific_env(char *cwd, t_env *env, char *key_value)
{
	char	**container;
	char	*oldpwd;
	int		x;

	x = 42;
	container = (char **)malloc(sizeof(char *) * 3);
	if (!container)
		return ;
	oldpwd = ft_strjoin(key_value, cwd);
	if (!oldpwd)
	{
		free(container);
		return ;
	}
	container[0] = ft_strdup("");
	container[1] = oldpwd;
	container[2] = 0;
	ft_add_node_env(container, env, &x);
	ft_free_array(container);
}
