/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:59:53 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/25 19:16:53 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
// Función para liberar la memoria de los tokens
*/
void	ft_free_tokens(t_tokens **lexer)
{
	t_tokens	*tmp;

	while (*lexer)
	{
		tmp = (*lexer)->next;
		free((*lexer)->value);
		free(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
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
