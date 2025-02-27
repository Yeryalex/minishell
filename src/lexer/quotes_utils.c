/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:00:55 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 11:08:59 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_double_quotes(const char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value[i])
		if (value[i++] == '"')
			count++;
	return (count);
}

int	ft_is_enclosed_by_single_quotes(const char *value)
{
	int	len;

	len = ft_strlen(value);
	return (len > 1 && value[0] == '\'' && value[len - 1] == '\'');
}

char	*ft_strip_outer_quotes(char *value)
{
	int		len;
	char	*trimmed;

	len = ft_strlen(value);
	trimmed = ft_substr(value, 1, len - 2);
	if (!trimmed)
	{
		free(value);
		return (NULL);
	}
	free(value);
	return (trimmed);
}
