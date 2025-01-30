/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:57 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/30 13:21:02 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
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

int	ft_exist_char(char *str)
{
	int i;
	int char_num;
	i = 0;
	char_num = 0;
	while (str[i])
	{
		if (str[i] == '=')
			char_num++;
		i++;
	}
	if (char_num == 1)
		return (1);
	else if (char_num > 1)
		return (char_num);
	return (0);
}

char	*ft_add_equals(int count)
{
	char *equals;
	int i;

	i = 0;
	equals = (char *)malloc(sizeof(char) * count);
	if (!equals)
		return (NULL);
	while (i < count)
	{
		equals[i] = '=';
		i++;
	}
	equals[i] = '\0';
	return (equals);
}

t_env	*ft_find_key_env(t_env *env, char *key_value)
{
	t_env	*temp;
	int i;

	i = 0;
	temp = env;
	while (temp)
	{	if (!ft_strcmp(temp->key, key_value))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_abletojoin(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] == '+' && str[i - 1] != '+')
			return (1);
	return (0);
}

t_env *ft_add_node_env(char **cmd_array, t_env *env)
{
	int i;
	t_env	*node;
	t_env	*temp;
	char	**key_value;
	int		concat_flag = 0;
	
	i = 1;
	while (cmd_array && cmd_array[i])
	{
		while (cmd_array[i] && cmd_array[i][0] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd_array[i]);
			i++;
		}

		if (!cmd_array[i])
			return (env);
		node = (t_env *)malloc(sizeof(t_env));
		node->next = NULL;
		
		key_value = ft_split(cmd_array[i], '=');
		int	add_equals = ft_exist_char(cmd_array[i]);
		
		if (ft_abletojoin(key_value[0]))
		{
			char *plus_join;

			plus_join = key_value[0];
			key_value[0] = ft_strtrim(key_value[0], "+");
			if (key_value[1])
				concat_flag = 1;
			free(plus_join);
		}
		
		t_env *node_with_key = ft_find_key_env(env, key_value[0]);
		printf("%i\n", concat_flag);

		char	*final_value;

		if (key_value[1])
			final_value = ft_strtrim(key_value[1], "\"\'");

		if (node_with_key && concat_flag)
		{
			char *value_join;
			value_join = key_value[1];
			
			if (node_with_key->value)
			{
				key_value[1] = ft_strjoin(node_with_key->value, key_value[1]);
				free(value_join);
			}
		/*	else
			{
				node_with_key->value = key_value[1];
				free(value_join);
			}*/
		}
		if (node_with_key)
		{
			if (add_equals)
			{
				if (node_with_key->value)
     				free(node_with_key->value);
			
 			if (final_value)
     			node_with_key->value = final_value;
 			else
     			node_with_key->value = NULL;
			}
			i++;
			continue ;
		}
		if (add_equals)
		{
			node->key = key_value[0];
			if (add_equals == 1)
			{
    			if (final_value)
        			node->value = final_value;
    			else
        			node->value = NULL;
			}
			else 
    			node->value = ft_strjoin(ft_add_equals(add_equals - 1), final_value);
		}
		else
		{
			
			node->key = key_value[0];
			node->value = final_value;
		}
        temp = env;
        while (temp->next)
			temp = temp->next;
		temp->next = node;
		i++;
	}
	return (env);
}

t_env	*ft_copy_envlst(t_env *env)
{
	t_env *new_node;
	t_env *new_env = NULL;
	t_env *current = NULL;
	
	while (env)
	{
		new_node = (t_env * )malloc(sizeof(t_env));
		if(!new_node)
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
	t_env *env_copy;

	if (cmd->cmd_array[1])
		ft_add_node_env(cmd->cmd_array, env);
	else
	{
		env_copy = ft_copy_envlst(env);
		ft_sort_env(env_copy);
		t_env *temp = env_copy;
		while (temp)
		{
			printf("declare -x %s", temp->key);
			if (temp->value)
				printf("=\"%s\"\n", temp->value);
			else 
				printf("\n");
			temp = temp->next;
		}
	}
	return (0);
}
