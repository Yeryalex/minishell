/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:16 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:18 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_type	ft_determine_type(char *value)
{
	if (!ft_strncmp(value, "|", 1))
		return (PIPE);
	if (!ft_strncmp(value, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(value, ">", 1))
		return (GTHAN);
	if (!ft_strncmp(value, "<<", 2))
		return (H_DOC);
	if (!ft_strncmp(value, "<", 1))
		return (STHAN);
	return (WORD);
}

t_tokens	*ft_init_node(void)
{
	t_tokens	*node;

	node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!node)
		return (ft_free_tokens(&node), NULL);
	node->prev = NULL;
	node->next = NULL;
	node->value = NULL;
	node->token = NONE;
	return (node);
}
