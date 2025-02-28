/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:40 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 11:04:05 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_unclosed_error(void)
{
	ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
	return (NULL);
}

char	*ft_get_word(const char **input)
{
	int		i;
	char	*value;
	char	quote;

	i = 0;
	quote = 0;
	while ((*input)[i] && (ft_is_metacharacter((*input)[i]) || quote != 0))
	{
		if ((*input)[i] == '"' || (*input)[i] == '\'')
		{
			if (quote == 0)
				quote = (*input)[i];
			else if ((*input)[i] == quote)
				quote = 0;
		}
		++i;
	}
	if (quote != 0)
		return (ft_unclosed_error());
	value = ft_substr(*input, 0, i);
	if (!value)
		return (NULL);
	*input = *input + i;
	return (value);
}

char	*ft_get_value(const char **input)
{
	char	*value;
	int		i;

	i = 0;
	if (ft_strncmp(*input, "||", 2) == 0)
	{
		ft_putstr_fd("minishell: error: found double token\n", 2);
		return (NULL);
	}
	if (ft_strchr("<>|", **input))
	{
		++i;
		if (!ft_strncmp(*input, "<<", 2) || !ft_strncmp(*input, ">>", 2))
			++i;
		value = ft_substr(*input, 0, i);
		*input += i;
	}
	else
		value = ft_get_word(input);
	if (!value)
		return (NULL);
	return (value);
}
