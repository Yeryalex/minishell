/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:39 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 15:23:01 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_start_expansion(char	**cmd, t_env *env)
{
	char	*new_var;
	t_env	*find_cmd;
	char	*temp;

	find_cmd = ft_find_key_env(env, *cmd + 1);
	if (find_cmd)
		new_var = find_cmd->value;
	else
		new_var = "";

	temp = *cmd;
	*cmd = ft_strdup(new_var);
	free(temp);
}

void	ft_expanser(t_cmds **cmd, t_utils *utils)
{
	int i;

	i = 0;
	while ((*cmd)->cmd_array[i])
	{
		if ((*cmd)->cmd_array[i][0] == '$')
		{
			ft_start_expansion(&(*cmd)->cmd_array[i], utils->environ);
		}
		i++;
	}
}
