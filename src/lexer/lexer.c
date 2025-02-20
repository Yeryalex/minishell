/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:29 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_find_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
/*
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
}*/
/*
void	ft_start_expansion(char *str_value, char *temp_str, int *i, int *j)
{
	while (str_value[*i])
	{
		if (str_value[*i] == '$' && str_value[*i + 1])
		{
			(*i)++;
		//	if ((*cmd)[*i] == '?')
		//	ft_apply_status(result, j, utils, i);
        //    else
        //	{
          //  	ft_create_expansion(*cmd, i, var_name);
            //	ft_find_command(var_name, result, j, utils->environ);          
		}
	}
}
*/
void	ft_double_quotes(t_utils *utils, char *temp_str, int *i, int *j)
{
	char	*str_value;

	str_value = utils->value_to_expand;
	printf("test %s\n", utils->value_to_expand);
	(*i)++;
	while (str_value[*i] && str_value[*i] != '"')
	{
		temp_str[(*j)++] = str_value[(*i)++];
	}
	(*i)++;
}

void	ft_single_quotes(char *str_value, char *temp_str, int *i, int *j)
{
	(*i)++;
	while (str_value[*i] && str_value[*i] != '\'')
	{
		temp_str[(*j)++] = str_value[(*i)++];
	}
	(*i)++;
}

char	*ft_create_new_str(int *i, int *j, t_utils *utils)
{
	char	*temp_str;
	char	*str_value;

	str_value = utils->value_to_expand;
	temp_str = (char *)malloc(ft_strlen(str_value) + 1);
	if (!temp_str)
		return (NULL);
	while (str_value[*i])
	{
		if (str_value[*i] == '\'')
			ft_single_quotes(str_value, temp_str, i, j);
		else if (str_value[*i] == '"')
			ft_double_quotes(utils, temp_str, i, j);
		else
			temp_str[(*j)++] = str_value[(*i)++];
	}
	temp_str[*j] = '\0';
	return (free(str_value), temp_str);
}

char	*ft_check_quotes(t_utils *utils)
{
	int		i;
	int		j;
	char	*str_value;

	str_value = utils->value_to_expand;
	if (!str_value)
		return (NULL);
	if (!ft_find_quotes(str_value))
		return (str_value);
	i = 0;
	j = 0;
	return(ft_create_new_str(&i, &j, utils));
}

t_tokens *ft_create_node(const char **input, t_utils* utils)
{
	char	*str_value;

	t_tokens *new_node = (t_tokens *)malloc(sizeof(t_tokens));
    if (!new_node)
        return (NULL);
    new_node->prev = NULL;
	new_node->next = NULL;
	str_value = ft_get_value(input);
	utils->value_to_expand = str_value;
	//new_node->value = ft_remove_quotes(str_value);
 	new_node->value = ft_check_quotes(utils);
	if (!new_node->value)
        return (free(new_node),NULL);
    new_node->token = ft_determine_type(new_node->value);
	return (new_node);
}

int	ft_addlast_node(t_tokens **lexer, t_tokens *current_node)
{
	t_tokens	*tmp_node;

	
	if (!*lexer)
	{
		*lexer = current_node;
		return (0);
	}
	tmp_node = *lexer;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	tmp_node->next = current_node;
	current_node->prev = tmp_node;
	return (0);
}

int	ft_check_pipes(t_tokens *lexer)
{
	t_tokens *temp;

	temp = lexer;
	if (!ft_strncmp(temp->value, "|", 1))
			return (0);
	while (temp)
	{
		if (!ft_strncmp(temp->value, "|", 1) && !temp->next)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_tokens	*ft_lexer_input(const char *input, t_utils *utils)
{
	t_tokens	*node;
	t_tokens	*lexer;
	
	lexer = NULL;

	if (!input)
		return (NULL);
	while(*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		node = ft_create_node(&input, utils);
		if (!node)
			return (ft_free_tokens(&lexer), NULL);
		if (ft_addlast_node(&lexer, node))
		{
			ft_free_tokens(&lexer);
			ft_free_tokens(&node);
			return (NULL);
		}
	}
	if (lexer)
	{
		if (!ft_check_pipes(lexer))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (ft_free_tokens(&lexer), NULL);
		}
	}
	return (lexer);
}
