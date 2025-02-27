/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expanser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:22:03 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 16:20:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_expand_with_quotes(int *i, int *j, t_utils *utils)
{
	char	*str_value;
	char	*temp_str;
	char	value_to_expand[255];

	str_value = utils->value_to_expand;
	temp_str = utils->temp_str;
	while (str_value[*i])
	{
		if (str_value[*i] == '$' && str_value[*i + 1])
			ft_expander_special(utils, i, j, value_to_expand);
		else
			temp_str[(*j)++] = str_value[(*i)++];
	}
}

char	*ft_quotes_in_hdoc(t_utils *utils)
{
	int		i;
	int		j;
	char	*str_value;

	i = 0;
	j = 0;
	str_value = utils->value_to_expand;
	if (!str_value)
		return (NULL);
	return (ft_expand_line(&i, &j, utils));
}
