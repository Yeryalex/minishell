/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:57 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/01 13:12:05 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_sort_env(t_env *env)
{
	t_env	*front;
	char	*temp_key;
	char	*temp_value;

	while (env)
	{
		front = env->next;
		while (front)
		{
			if (ft_strcmp(env->key, front->key) > 0)
			{
				temp_key = env->key;
				env->key = front->key;
				front->key = temp_key;
				temp_value = env->value;
				env->value = front->value;
				front->value = temp_value;
			}
			front = front->next;
		}
		env = env->next;
	}
}

t_env	*ft_find_key_env(t_env *env, char *key_value)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key_value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_abletojoin(char *str)
{
	int	plus;
	int	i;

	i = 0;
	plus = 0;
	while (str[i])
	{
		if (str[i] == '+')
			plus++;
		i++;
	}
	if (plus == 1)
		return (1);
	else if (plus > 1)
		return (2);
	return (0);
}

int	ft_key_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	ft_check_identifier(char **cmd_array, int *i)
{
	while (cmd_array[*i] && cmd_array[*i][0] == '=')
	{
		printf("minishell: export: `%s'", cmd_array[*i]);
		printf(": not a valid identifier\n");
		(*i)++;
	}
}

void	ft_init_key_value(char **cmd_array, char **x_key, char **x_value, int *i, int *flag)
{
	int		end_key;
	char	*temp_x_value;
	char	*temp_key;

	end_key = ft_key_end(cmd_array[*i]);
	if (end_key)
	{
		*x_key = ft_substr(cmd_array[*i], 0, end_key);
		*x_value = ft_substr(cmd_array[*i], end_key + 1,
				ft_strlen(cmd_array[*i]));
	}
	else
		*x_key = ft_strdup(cmd_array[*i]);
	if (ft_abletojoin(*x_key))
	{
		temp_key = *x_key;
		*x_key = ft_strtrim(*x_key, "+");
		free(temp_key);
		*flag = 1;
	}
	temp_x_value = *x_value;
	*x_value = ft_strtrim(*x_value, "\"\'");
	free(temp_x_value);
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

	if (node_already_exist->value)
	{
		temp_value = node_already_exist->value;
		node_already_exist->value = ft_strjoin(temp_value, *x_value);
		free(temp_value);
	}
	else
	{
		if (*x_value)
			node_already_exist->value = *x_value;
	}
}

void	ft_flag_case2(t_env *node_already_exist, char **x_value)
{
	if (node_already_exist->value == NULL)
		node_already_exist->value = *x_value;
	else
	{
		free(node_already_exist->value);
		if (*x_value)
			node_already_exist->value = *x_value;
	}
}

void	ft_check_nodes(t_env *node_already_exist, char **x_key, char **x_value, t_env *env, int *flag)
{
	if (node_already_exist)
	{
		if (*flag == 1)
			ft_flag_case1(node_already_exist, x_value);
		else
			ft_flag_case2(node_already_exist, x_value);
	}
	else
		ft_create_new_node(x_key, x_value, env);
}

t_env	*ft_add_node_env(char **cmd_array, t_env *env)
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
		x_key = NULL;
		x_value = NULL;
		ft_check_identifier(cmd_array, &i);
		if (!cmd_array[i])
			return (env);
		ft_init_key_value(cmd_array, &x_key, &x_value, &i, &flag);
		node_already_exist = ft_find_key_env(env, x_key);
		ft_check_nodes(node_already_exist, &x_key, &x_value, env, &flag);
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

int	ft_export(t_cmds *cmd, t_env *env)
{
	t_env	*temp;
	t_env	*env_copy;

	if (cmd->cmd_array[1])
		ft_add_node_env(cmd->cmd_array, env);
	else
	{
		env_copy = ft_copy_envlst(env);
		ft_sort_env(env_copy);
		temp = env_copy;
		while (temp)
		{
			printf("declare -x %s", temp->key);
			if (temp->value)
				printf("=\"%s\"\n", temp->value);
			else
				printf("\n");
			temp = temp->next;
		}
		ft_clear_lstenv(env_copy);
	}
	return (0);
}
