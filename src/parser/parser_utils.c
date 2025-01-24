/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:27:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/24 10:09:07 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_addlast_pnode(t_cmds **list, t_cmds *node)
{
	t_cmds	*current_node;

	if (!*list)
	{
		*list = node;
		return ;
	}
	current_node = *list;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = node;
	node->prev = current_node;
}
