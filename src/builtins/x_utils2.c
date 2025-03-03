/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:17:47 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 11:30:45 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_check_identifier(char **cmd_array, int *i, int *exit_status)
{
	if (*exit_status == 42)
		return ;
	while (cmd_array[*i] && (cmd_array[*i][0] == '='
		|| ft_isdigit(cmd_array[*i][0])))
	{
		printf("minishell: export: `%s'", cmd_array[*i]);
		printf(": not a valid identifier\n");
		*exit_status = 1;
		(*i)++;
	}
	while (cmd_array[*i] && ((ft_abletojoin(cmd_array[*i]) > 1)
			|| ft_valid_export(cmd_array[*i])))
	{
		printf("minishell: export: `%s'", cmd_array[*i]);
		printf(": not a valid identifier\n");
		*exit_status = 1;
		(*i)++;
	}
}

int	ft_init_key_value(char **cmd_array, char **x_key, char **x_value, int *i)
{
	int		end_key;
	char	*temp_key;
	int		flag;

	flag = 0;
	end_key = ft_key_end(cmd_array[*i]);
	if (end_key)
	{
		*x_key = ft_substr(cmd_array[*i], 0, end_key);
		*x_value = ft_substr(cmd_array[*i], end_key + 1,
				ft_strlen(cmd_array[*i]));
	}
	else
	{
		*x_key = ft_strdup(cmd_array[*i]);
		*x_value = NULL;
	}
	if (ft_abletojoin(*x_key) == 1)
	{
		temp_key = *x_key;
		*x_key = ft_strtrim(*x_key, "+");
		free(temp_key);
		flag = 1;
	}
	return (flag);
}

void	ft_create_new_node(char **x_key, char **x_value, t_env *env)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		free(*x_key);
		free(*x_value);
		return ;
	}
	new_node->next = NULL;
	new_node->key = *x_key;
	new_node->value = *x_value;
	temp = env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	ft_flag_case1(t_env *node_already_exist, char **x_value)
{
	char	*temp_value;

	temp_value = node_already_exist->value;
	if (node_already_exist->value)
	{
		if (*x_value)
		{
			node_already_exist->value = ft_strjoin(temp_value, *x_value);
			free(temp_value);
			free(*x_value);
		}
	}
	else
	{
		if (*x_value)
		{
			node_already_exist->value = ft_strdup(*x_value);
			free(x_value);
		}
	}
}
