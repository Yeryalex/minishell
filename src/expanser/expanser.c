/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:39 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 19:47:21 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_valid_env(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

void	ft_create_expansion(char *cmd, int *i, char *var_name)
{
	int	k;

	k = 0;
	while (cmd[*i] && ft_valid_env(cmd[*i]))
		var_name[k++] = cmd[(*i)++];
	var_name[k] = '\0';
}

void	ft_find_command(char *var_name, char *result, int *j, t_env *env)
{
	char	*new_var;
	t_env	*find_cmd;

	find_cmd = ft_find_key_env(env, var_name);
	if (find_cmd)
		new_var = find_cmd->value;
	else
		new_var = "";
	while (*new_var)
		result[(*j)++] = *new_var++;
}

void	ft_start_expansion(char **cmd, t_env *env)
{
	char	result[1024];
	char	var_name[256];
	char	*old_cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_cmd = *cmd;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '$' && (*cmd)[i + 1])
		{
			i++;
			ft_create_expansion(*cmd, &i, var_name);
			ft_find_command(var_name, result, &j, env);
		}
		else
			result[j++] = (*cmd)[i++];
	}
	result[j] = '\0';
	*cmd = strdup(result);
	free(old_cmd);
}

void	ft_expanser(char **cmd, t_utils *utils)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
			ft_start_expansion(&cmd[i], utils->environ);
		i++;
	}
}
