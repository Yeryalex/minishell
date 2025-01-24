/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/24 10:20:19 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds *ft_create_node_cmd(t_tokens *lexer, int count, char *path)
{
	t_cmds *node_cmd;
    int i;

	if (!lexer || count <= 0)
        return (NULL);

    node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
    if (!node_cmd)
		ft_free_cmd(node_cmd);
    node_cmd->cmd_array = (char **)malloc((count + 1) * sizeof(char *));
    if (!node_cmd->cmd_array)
        ft_free_cmd(node_cmd);
    i = 0;
    while (lexer && lexer->token != PIPE && i < count)
    {
        node_cmd->cmd_array[i] = ft_strdup(lexer->value);
        if (!node_cmd->cmd_array[i])
			ft_free_cmd(node_cmd);
        i++;
        lexer = lexer->next;
    }
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	node_cmd->cmd_array[i] = NULL;
    node_cmd->next = NULL;
    return (node_cmd);
}

t_cmds *ft_parser(t_tokens *lexer, char *path)
{
    t_cmds *all_cmds;
    t_cmds *last_cmd;
	t_cmds *new_cmd;
    t_tokens *head_parser; 
    t_tokens *parser;
	char *cmd_path;
	int count_tokens = 0;

    head_parser = lexer;
	parser = lexer;
	all_cmds = NULL;
	last_cmd = NULL;
	new_cmd = NULL;
	count_tokens = 0;
	// Validacion inicial: verifica si el primer token es un PIPE
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
				{
					ft_free_cmd(new_cmd);
					return (NULL);
				}
            	if (last_cmd)  
                	last_cmd->next = new_cmd;
            	else
                	all_cmds = new_cmd;
            	last_cmd = new_cmd;
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
		{
			ft_free_cmd(new_cmd);
        	return (NULL);
		}
    	if (last_cmd)
        	last_cmd->next = new_cmd;
    	else
        	all_cmds = new_cmd;
    }
	else if (parser && parser->token == PIPE)
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	return (all_cmds);
}
