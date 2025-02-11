/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:59:53 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 19:31:23 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_tokens(t_tokens **tokens)
{
	t_tokens	*temp;
		
	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = temp;
	}
}

int	ft_is_metacharacter(int c)
{
	if (!ft_isspace(c) && !ft_strchr("<>|", c))
		return (1);
	return (0);
}

void	ft_skip_spaces_and_quotes(char **input)
{
	char	quote_type;

	while (**input && ft_isspace(**input))
		(*input)++;
	if (**input == '\'' || **input == '"')
	{
		quote_type = **input;
		(*input)++;
		while (**input && **input != quote_type)
			(*input)++;
		if (**input == quote_type)
			(*input)++;
	}
}
