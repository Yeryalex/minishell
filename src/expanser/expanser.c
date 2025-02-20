/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:39 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 13:19:19 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

static int	ft_valid_env(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
}

static 	void ft_create_expansion(char *cmd, int *i, char *var_name)
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

void    ft_assign_status(char *result, int *j, t_utils *utils)
{
    char    *value;
    int     k;

    k = 0;
    value = ft_itoa(utils->exit_status);
    while (value[k])
        result[(*j)++] = value[k++];
    free(value);
}

void	ft_apply_status(char *result, int *j, t_utils *utils, int *i)
{
	ft_assign_status(result, j, utils);
	(*i)++;
}

static void	ft_start_expansion(char **cmd, t_utils *utils, int *j, int *i)
{
	char	result[1024];
	char	var_name[256];
	char	*old_cmd;

	old_cmd = *cmd;
	while ((*cmd)[*i])
	{
		if ((*cmd)[*i] == '$' && (*cmd)[*i + 1])
		{
			if (!(*cmd)[*i + 1] || (*cmd)[*i + 1] == ' ' || (*cmd)[*i + 1] == '$')
				result[(*j)++] = (*cmd)[(*i)++];
            else
			{
				(*i)++;
				if ((*cmd)[*i] == '?')
					ft_apply_status(result, j, utils, i);
            	else
            	{
                	ft_create_expansion(*cmd, i, var_name);
                	ft_find_command(var_name, result, j, utils->environ);
            	}
			}
		}
		else
			result[(*j)++] = (*cmd)[(*i)++];
	}
	result[*j] = '\0';
	*cmd = strdup(result);
	free(old_cmd);
}

void	ft_expanser(char **cmd, t_utils *utils)
{
	int	i;
	int	j;
	int	k;

	if (!*cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		j = 0;
		k = 0;
		if (ft_strchr(cmd[i], '$'))
			ft_start_expansion(&cmd[i], utils, &j, &k);
		i++;
	}
}
