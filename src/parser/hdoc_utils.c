/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:45:40 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 13:47:21 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_hdoc_error_handler(t_dir *redir, t_cmds *cmds)
{
	unlink(redir->filename);
	free(redir->filename);
	free(redir);
	if (cmds)
		cmds->error_fd = 1;
	return (NULL);
}

int	ft_hdoc_quotes(t_tokens *lexer)
{
	while (lexer)
	{
		if (lexer->next)
			if (ft_strchr(lexer->next->value, '"') \
					|| ft_strchr(lexer->next->value, '\''))
				return (1);
		lexer = lexer->next;
	}
	return (0);
}

void	ft_free_child_hdoc(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	if (lexer && *lexer)
		ft_free_tokens(lexer);
	if (cmds)
		ft_free_cmd(cmds);
	if (utils)
		ft_free_utils(utils);
}

void	ft_cleanup_child_hdoc(t_tokens **lexer,
		t_cmds *cmds, t_utils *utils, t_dir *redir)
{
	ft_free_child_hdoc(lexer, cmds, utils);
	free(redir->filename);
	free(redir);
}
