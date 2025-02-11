/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/07 12:43:44 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_init_cmd_node(t_cmds *node, int num)
{
	if (num > 0)
	{
		node->cmd_array = (char **)malloc((num + 1) * sizeof(char *));
		if (!node->cmd_array)
			return (free(node->cmd_array), -1);
		node->cmd_array[num] = NULL;
	}
	else
		node->cmd_array = NULL;
	//node->error_fd = 0;
	node->full_path = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	return (0);
}

static int	ft_fill_cmd_array(t_cmds *node, t_tokens *lexer, int count)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE && i < count)
	{
		node->cmd_array[i] = ft_strdup(lexer->value);
		if (!node->cmd_array[i])
			return (free_cmd_array(node->cmd_array), free(node), -1);
			//return (-1);
		i++;
		lexer = lexer->next;
	}
	node->cmd_array[i] = NULL;
	return (0);
}

t_cmds *ft_create_node_cmd(t_tokens *lexer, int count_tokens, char *path)
{
	t_cmds	*node_cmd;

	if (!lexer)
		return (NULL);
		//return (ft_free_tokens(&lexer), NULL);
	node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node_cmd || ft_init_cmd_node(node_cmd, count_tokens) == -1)
		return (ft_free_tokens(&lexer), NULL);
		//return (NULL);
	if (ft_fill_cmd_array(node_cmd, lexer, count_tokens) == -1)
		return (NULL);
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	if (!node_cmd->full_path)
		return (free_cmd_array(node_cmd->cmd_array), free(node_cmd), NULL);
		//return (NULL);
	return (node_cmd);
}

static int	ft_process_pipe(t_cmds **all_cmds, int count_tokens, t_tokens **head, char *path)
{
	t_cmds	*new_cmd;

	if (count_tokens == 0)
		return (perror("minishell: syntax error near unexpected token `|\'\n"), 0);
	new_cmd = ft_create_node_cmd(*head, count_tokens, path);
	if (!new_cmd)
		return (ft_free_cmd(*all_cmds), 0);
	ft_addlast_pnode(all_cmds, new_cmd);
	return (1);
}

t_cmds *ft_parser(t_tokens *lexer, char *path)
{
	t_cmds		*all_cmds;
	t_tokens	*head_parser;
	int			count_tokens;

	all_cmds = NULL;
	head_parser = lexer;
	count_tokens = 0;
	if (lexer && lexer->token == PIPE)
		return (perror("minishell: syntax error near unexpected token `|\'\n"), NULL);
	while (lexer)
	{
		if (lexer->token == WORD)
			count_tokens++;
		else if (lexer->token == PIPE)
		{
			if (ft_process_pipe(&all_cmds, count_tokens, &head_parser, path) == 0)
				return(NULL);
			head_parser = lexer->next;
			count_tokens = 0;
		}
		lexer = lexer->next;
	}
	if (count_tokens >= 0)
		if (ft_process_pipe(&all_cmds, count_tokens, &head_parser, path) == 0)
			return(NULL);
	return (all_cmds);
}
