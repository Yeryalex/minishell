/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:15:20 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/10 08:15:43 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*ft_clear_add_lstenv(t_env *env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = 

	}


}

t_env	*ft_create_node_env(char **env)
{


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
			ft_clear_add_lstenv(lst_env);
			return (NULL);
		}


		env++;

	}
	return (lst_env);
}
