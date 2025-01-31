/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/29 10:19:17 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds *ft_create_node_cmd(t_tokens *lexer, int count_tokens, char *path)
{
	t_cmds *node_cmd;
    int i;

	if (!lexer || count_tokens <= 0)
	{
		ft_free_tokens(&lexer);
        return (NULL);
	}
    node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
    if (!node_cmd)
		ft_free_cmd(node_cmd);
    node_cmd->cmd_array = (char **)malloc((count_tokens + 1) * sizeof(char *));
    if (!node_cmd->cmd_array)
        ft_free_cmd(node_cmd);
    i = 0;
    while (lexer && lexer->token != PIPE && i < count_tokens)
    {
        node_cmd->cmd_array[i] = ft_strdup(lexer->value);
        if (!node_cmd->cmd_array[i])
			ft_free_cmd(node_cmd);
        i++;
        lexer = lexer->next;
    }
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	node_cmd->cmd_array[count_tokens] = NULL;
    node_cmd->next = NULL;
    node_cmd->prev = NULL;
	return (node_cmd);
}

t_cmds *ft_parser(t_tokens *lexer, char *path)
{
    t_cmds *all_cmds;
 	t_cmds *new_cmd;
    t_tokens *head_parser; 
    t_tokens *parser;
	char *cmd_path;
	int count_tokens = 0;

    head_parser = lexer;
	parser = lexer;
	all_cmds = NULL;
	new_cmd = NULL;
	count_tokens = 0;
	if (parser && parser->token == PIPE)
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	cmd_path = path;
	while (parser)
	{
    	if (parser->token == WORD)
    	   	count_tokens++;
    	else if (parser->token == PIPE)
    	{
        	if (count_tokens > 0)
        	{
            	new_cmd = ft_create_node_cmd(head_parser, count_tokens, cmd_path);
            	if (!new_cmd)
					return(ft_free_cmd(new_cmd), NULL);
				ft_addlast_pnode(&all_cmds, new_cmd);
        	}
			else
        	{
            	perror("syntax error near unexpected token `|\'\n");
            	return (NULL);
        	}
			head_parser = parser->next;
        	count_tokens = 0;
    	}
    	parser = parser->next;
	}
	if (count_tokens > 0)
	{
    	new_cmd = ft_create_node_cmd(head_parser, count_tokens, cmd_path);
    	if (!new_cmd)
			return (ft_free_cmd(new_cmd), NULL);
		ft_addlast_pnode(&all_cmds, new_cmd);
    }
	else if (parser && parser->token == PIPE)
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	return (all_cmds);
}
