/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:20:57 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/26 11:37:10 by rbuitrag         ###   ########.fr       */
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

char	*ft_create_new_str(int *i, int *j, t_utils *utils)
{
	char	*temp_str;
	char	*str_value;

	str_value = utils->value_to_expand;
	temp_str = (char *)malloc(ft_strlen(str_value) + 1000);
	if (!temp_str)
		return (NULL);
	utils->temp_str = temp_str;
	while (str_value[*i])
	{
		if (str_value[*i] == '\'')
			ft_single_quotes(str_value, temp_str, i, j);
		else if (str_value[*i] == '"')
			ft_double_quotes(utils, temp_str, i, j);
		else
		{	if (str_value[*i] == '$')
				ft_expansion(i, j, utils); //ft_expansion(temp_str, i, j, utils);
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
