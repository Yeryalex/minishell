/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 11:38:02 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_handle_redirections(t_tokens **lexer, t_cmds *node, t_utils *utils)
{
	if ((*lexer)->token == GTHAN || (*lexer)->token == APPEND)
	{
		if (ft_gthan_append_cmds(lexer, node, utils) == -1)
			return (-1);
	}
	else if ((*lexer)->token == STHAN || (*lexer)->token == H_DOC)
	{
		if (ft_sthan_hdoc_cmds(lexer, node, utils) == -1)
			return (-1);
	}
	return (0);
}

static int	ft_fill_cmd(t_cmds *node, t_tokens *lexer, int count, t_utils *utils)
{
	int	i;

	(void)count;
	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == WORD)
		{
			if (!lexer->prev || (lexer->prev->token != GTHAN
				&& lexer->prev->token != APPEND && lexer->prev->token != STHAN
				&& lexer->prev->token != H_DOC))
			{		
				node->cmd_array[i++] = ft_strdup(lexer->value);
			}
			lexer = lexer->next;
			continue ;
		}
		if (!utils->redir_error && ft_handle_redirections(&lexer, node, utils) == -1)
			return (-1);
		utils->redir_error = 0;
		lexer = lexer->next;
	}
	node->cmd_array[i] = NULL;
	return (0);
}

t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count_tokens, char *path, t_utils *utils)
{
	t_cmds	*node_cmd;

	if (!lexer)
		return (NULL);
	node_cmd = malloc(sizeof(t_cmds));
	if (!node_cmd)
		return (NULL);
	if (ft_init_cmd_node(node_cmd, count_tokens) == -1)
		return (ft_free_tokens(&lexer), NULL);
	if (ft_fill_cmd(node_cmd, lexer, count_tokens, utils) == -1)
		return (ft_free_cmd(node_cmd), NULL);
	ft_set_full_path(node_cmd, path);
	if (lexer && lexer->next && lexer->token == PIPE)
		lexer = lexer->next;
	return (node_cmd);
}

static int	ft_process_pipe(t_cmds **all_cmds, int count_tokens, t_tokens **head, char *path, t_utils *utils)
{
	t_cmds	*new_cmd;

	new_cmd = ft_create_node_cmd(*head, count_tokens, path, utils);
	if (!new_cmd)
		return (ft_free_cmd(*all_cmds), 0);
	ft_addlast_pnode(all_cmds, new_cmd);
	*head = (*head)->next;
	return (1);
}

t_cmds	*ft_parser(t_tokens *lexer, char *path, t_utils *utils)
{
	t_cmds		*all_cmds;
	t_tokens	*head_parser;
	int			count_tokens;

	all_cmds = NULL;
	head_parser = lexer;
	count_tokens = 0;
	while (lexer)
	{
		if (lexer->token == WORD)
			count_tokens++;
		else if (lexer->token == PIPE)
		{
			if (!ft_process_pipe(&all_cmds, count_tokens, &head_parser, path, utils))
				return (NULL);
			head_parser = lexer->next;
			count_tokens = 0;
		}
		lexer = lexer->next;
	}
	if (count_tokens >= 0)
		if (!ft_process_pipe(&all_cmds, count_tokens, &head_parser, path, utils))
			return (NULL);
	return (all_cmds);
}
