/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expanser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:16:01 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/24 19:54:35 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_assign_status(char *temp_str, int *j, t_utils *utils)
{
	char	*value;
	int		k;

	k = 0;
	value = ft_itoa(utils->exit_status);
	while (value[k])
		temp_str[(*j)++] = value[k++];
	free(value);
}

void	ft_expander_special(t_utils *utils, int *i,
		int *j, char *value_to_expand)
{
	char	*str_value;
	char	*temp_str;

	str_value = utils->value_to_expand;
	temp_str = utils->temp_str;
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

int	ft_check_special_char(char *str_value, int *i)
{
	return ((str_value[*i + 1] == '"' || str_value[*i + 1] == '$'
			|| str_value[*i + 1] == ' '));
}
