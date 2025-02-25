/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:57 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 11:18:23 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_flag_case2(t_env *node_already_exist, char **x_value)
{
	char	*temp_value;

	if (node_already_exist->value)
	{
		temp_value = node_already_exist->value;
		if (*x_value)
		{
			node_already_exist->value = *x_value;
			free(temp_value);
		}
	}
	else
	{
		if (*x_value)
			node_already_exist->value = *x_value;
		else
			node_already_exist->value = NULL;
	}
}

void	ft_check_nodes(t_env *node_already_exist, char **x_value, int *flag)
{
	if (*flag == 1)
		ft_flag_case1(node_already_exist, x_value);
	else
		ft_flag_case2(node_already_exist, x_value);
}

t_env	*ft_add_node_env(char **cmd_array, t_env *env, int *exit_status)
{
	int		i;
	t_env	*node_already_exist;
	int		flag;
	char	*x_key;
	char	*x_value;

	i = 1;
	flag = 0;
	while (cmd_array && cmd_array[i])
	{
		ft_check_identifier(cmd_array, &i, exit_status);
		if (!cmd_array[i])
			return (env);
		flag = ft_init_key_value(cmd_array, &x_key, &x_value, &i);
		node_already_exist = ft_find_key_env(env, x_key);
		if (node_already_exist)
		{
			ft_check_nodes(node_already_exist, &x_value, &flag);
			free(x_key);
		}
		else
			ft_create_new_node(&x_key, &x_value, env);
		i++;
	}
	return (env);
}

t_env	*ft_copy_envlst(t_env *env)
{
	t_env	*new_node;
	t_env	*new_env;
	t_env	*current;

	new_env = NULL;
	current = NULL;
	while (env)
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(env->key);
		if (env->value)
			new_node->value = ft_strdup(env->value);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		if (!new_env)
			new_env = new_node;
		else
			current->next = new_node;
		current = new_node;
		env = env->next;
	}
	return (new_env);
}

int	ft_export(t_cmds *cmd, t_env *env, int fd)
{
	t_env	*temp;
	t_env	*env_copy;
	int		exit_status;

	exit_status = 0;
	if (cmd->cmd_array[1])
		ft_add_node_env(cmd->cmd_array, env, &exit_status);
	else
	{
		env_copy = ft_copy_envlst(env);
		ft_sort_env(env_copy);
		temp = env_copy;
		while (temp)
		{
			//printf("declare -x %s", temp->key);
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(temp->key, fd);
			if (temp->value)
			{
				ft_putstr_fd("=\"", fd);//printf("=\"%s\"\n", temp->value);
				ft_putstr_fd(temp->value, fd);
				ft_putstr_fd("\"\n", fd);
			}
			else
				ft_putstr_fd("\"\n", fd);//printf("\n");
			temp = temp->next;
		}
		ft_clear_lstenv(env_copy);
	}
	return (exit_status);
}
