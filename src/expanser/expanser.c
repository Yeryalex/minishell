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


void    ft_assign_status(char *temp_str, int *j, t_utils *utils)
{
    char    *value;
    int     k;

    k = 0;
    value = ft_itoa(utils->exit_status);
    while (value[k])
        temp_str[(*j)++] = value[k++];
    free(value);
}

void	ft_apply_status(char *temp_str, int *j, t_utils *utils, int *i)
{
	ft_assign_status(temp_str, j, utils);
	(*i)++;
}

void	ft_create_expansion(t_utils *utils, char *value_to_expand, int *i)
{
	char	*str_value;
	int		k;

	k = 0;
	str_value = utils->value_to_expand;
	while (str_value[*i] && ft_valid_env(str_value[*i]))
		value_to_expand[k++] = str_value[(*i)++];
	value_to_expand[k] = '\0';
}

void	ft_expand_variable(t_utils *utils, char *value_to_expand, char *temp_str, int *j)
{
	char	*new_var;
	t_env	*find_cmd;

	find_cmd = ft_find_key_env(utils->environ, value_to_expand);
	if (find_cmd)
		new_var = find_cmd->value;
	else
		new_var = "";
	while (*new_var)
		temp_str[(*j)++] = *new_var++;
}

void	ft_expansion(char *temp_str, int *i, int *j, t_utils *utils)
{
	char	*str_value;
	char	value_to_expand[255];

	str_value = utils->value_to_expand;
	while (str_value[*i])
	{
		if (str_value[*i] == '$' && str_value[*i + 1])
		{
			if (str_value[*i + 1] == '$')
				temp_str[(*j)++] = str_value[(*i)++];
			else
			{
				(*i)++;
				if (str_value[*i] == '?')
					ft_apply_status(temp_str, j, utils, i);
				else
				{
					ft_create_expansion(utils, value_to_expand, i);
            		ft_expand_variable(utils, value_to_expand, temp_str, j);          
				}
			}
		}
		else
		{
			if (str_value[*i] == '"')
				ft_double_quotes(utils, temp_str, i, j);
			else if (str_value[*i] == '\'')
				ft_single_quotes(str_value, temp_str, i, j);
			else
				temp_str[(*j)++] = str_value[(*i)++];
		}
	}
}

void	ft_start_expansion(t_utils *utils, char *temp_str, int *i, int *j)
{
	char	*str_value;
	char	value_to_expand[255];

	str_value = utils->value_to_expand;
	while (str_value[*i] && str_value[*i] != '"')
	{
		if (str_value[*i] == '$' && str_value[*i + 1])
		{
			if (str_value[*i + 1] == '"' || str_value[*i + 1] == '$' || str_value[*i + 1] == ' ')
				temp_str[(*j)++] = str_value[(*i)++];
			else
			{
				(*i)++;
				if (str_value[*i] == '?')
					ft_apply_status(temp_str, j, utils, i);
				else
				{
					ft_create_expansion(utils, value_to_expand, i);
            		ft_expand_variable(utils, value_to_expand, temp_str, j);          
				}
			}    
		}
		else
			temp_str[(*j)++] = str_value[(*i)++];
	}
}


/*
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

static void    ft_assign_status(char *result, int *j, t_utils *utils)
{
    char    *value;
    int     k;

    k = 0;
    value = ft_itoa(utils->exit_status);
    while (value[k])
        result[(*j)++] = value[k++];
    free(value);
}

static void	ft_apply_status(char *result, int *j, t_utils *utils, int *i)
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
*/