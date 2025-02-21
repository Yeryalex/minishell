/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:20:57 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/30 19:21:00 by rbuitrag         ###   ########.fr       */
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

int	ft_valid_env(char c)
{
	return (c == '_' || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}
/*
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
*/
void	ft_double_quotes(t_utils *utils, char *temp_str, int *i, int *j)
{
	char	*str_value;

	str_value = utils->value_to_expand;
	(*i)++;
	while (str_value[*i] && str_value[*i] != '"')
	{
		if (str_value[*i] == '$')
			ft_start_expansion(utils, temp_str, i, j);
		else
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

/*

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
*/
char	*ft_create_new_str(int *i, int *j, t_utils *utils)
{
	char	*temp_str;
	char	*str_value;

	str_value = utils->value_to_expand;
	temp_str = (char *)malloc(ft_strlen(str_value) + 1000);
	if (!temp_str)
		return (NULL);
	while (str_value[*i])
	{
		if (str_value[*i] == '\'')
			ft_single_quotes(str_value, temp_str, i, j);
		else if (str_value[*i] == '"')
			ft_double_quotes(utils, temp_str, i, j);
		else
		{	if (str_value[*i] == '$')
				ft_expansion(temp_str, i, j, utils);
			else
				temp_str[(*j)++] = str_value[(*i)++];
		}
	}
	temp_str[*j] = '\0';
	return (free(str_value), temp_str);
}

char	*ft_check_quotes(t_utils *utils)
{
	int		i;
	int		j;
	char	*str_value;

	i = 0;
	j = 0;
	str_value = utils->value_to_expand;
	if (!str_value)
		return (NULL);
	return(ft_create_new_str(&i, &j, utils));
}


/*
static int	ft_validate_quotes(const char *value)
{
	char	quote_type;
	int		i;
	int		opened;

	i = 0;
	opened = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			quote_type = value[i++];
			opened++;
			while (value[i] && value[i] != quote_type)
				i++;
			if (value[i] == quote_type)
				opened--;
		}
		if (value[i])
			i++;
	}
	if (opened > 0)
		return (printf("Unexpected close quote\n"), 0);
	return (1);
}


static void	ft_process_quotes(char *value, char *result, int inside_double)
{
	int	i;
	int	j;
	int	single_quotes;

	i = 0;
	j = 0;
	single_quotes = 0;
	while (value[i])
	{
		if (value[i] == '"' && !single_quotes)
			i++;
		else if (value[i] == '\'' && inside_double)
			result[j++] = value[i++];
		else if (value[i] == '\'')
			i++;
		else
			result[j++] = value[i++];
	}
	result[j] = '\0';
}

char	*ft_remove_quotes(char *value)
{
	char	*result;
	int		len;
	int		double_quotes;
	int		inside_double_quotes;

	if (!value || !ft_validate_quotes(value))
		return (free(value), NULL);
	if (ft_is_enclosed_by_single_quotes(value))
	{
		if (*(value + 1) == '"')
			return (ft_strip_outer_quotes(value));
		else
			return (value);
	}
	len = ft_strlen(value);
	double_quotes = ft_count_double_quotes(value);
	inside_double_quotes = (double_quotes / 2) % 2;
	result = (char *)malloc(len + 1);
	if (!result)
		return (free(value), NULL);
	ft_process_quotes(value, result, inside_double_quotes);
	free(value);
	return (result);
}
*/