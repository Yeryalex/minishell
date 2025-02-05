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
		return (ft_strip_outer_quotes(value));
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
