/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:39 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/21 11:31:22 by yrodrigu         ###   ########.fr       */
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
