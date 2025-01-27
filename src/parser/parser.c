/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/27 12:16:13 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	*free_cmd_array(char **cmd_array)
{
	int		i;

	if (cmd_array)
	{
		i = 0;
		while (cmd_array[i])
		{
			free (cmd_array[i]);
			cmd_array[i] = NULL;
			i++;
		}
		free(cmd_array);
	}
	return (NULL);
}

t_cmds *ft_create_node_cmd(t_tokens *lexer, int count_tokens, char *path)
{
	t_cmds *node_cmd;
    int i;

	if (!lexer || count_tokens <= 0)
		return (ft_free_tokens(&lexer), NULL);
	node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
    if (!node_cmd)
        return (ft_free_cmd(node_cmd), NULL);
    node_cmd->cmd_array = (char **)malloc((count_tokens + 1) * sizeof(char *));
    if (!node_cmd->cmd_array)
       // return(ft_free_cmd(node_cmd), NULL);
	{
		free_cmd_array(node_cmd->cmd_array);
		return(free(node_cmd), NULL);
	}
    i = 0;
    while (lexer && lexer->token != PIPE && i < count_tokens)
    {
        node_cmd->cmd_array[i] = ft_strdup(lexer->value);
        if (!node_cmd->cmd_array[i])
		{
			free_cmd_array(node_cmd->cmd_array);
			return (ft_free_cmd(node_cmd), NULL);
		}
		i++;
        lexer = lexer->next;
    }
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	if (!node_cmd->full_path)
    {
        free_cmd_array(node_cmd->cmd_array);
        ft_free_cmd(node_cmd);
        return (NULL);
    }
	node_cmd->cmd_array[i] = NULL;
    node_cmd->next = NULL;
	if (!node_cmd)
			return (ft_free_cmd(node_cmd), NULL);
	return (node_cmd);
}

t_cmds *ft_parser(t_tokens *lexer, char *path)
{
    t_cmds *all_cmds;
 	t_cmds *new_cmd;
    t_tokens *head_parser; 
    t_tokens *parser;
	int count_tokens;

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
	while (parser)
	{
    	if (parser->token == WORD)
    	   	count_tokens++;
    	else if (parser->token == PIPE)
    	{
        	if (count_tokens > 0)
        	{
            	new_cmd = ft_create_node_cmd(head_parser, count_tokens, path);
            	if (!new_cmd)
				{
					ft_free_tokens(&head_parser);
                    ft_free_cmd(all_cmds);
                    return (NULL);
				}

					//return(ft_free_cmd(new_cmd), NULL);
				//if (!new_cmd->cmd_array)
				//	new_cmd->cmd_array = free_cmd_array(new_cmd->cmd_array);
			//	free(new_cmd);
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
    	new_cmd = ft_create_node_cmd(head_parser, count_tokens, path);
    	if (!new_cmd)
		{
			ft_free_tokens(&head_parser);
			ft_free_cmd(all_cmds);
			//ft_free_cmd(new_cmd);
			return (NULL);
		//	free(cmd_path);
			//return (ft_free_cmd(new_cmd), NULL);
		}
		ft_addlast_pnode(&all_cmds, new_cmd);
    }
//	else if (parser && parser->token == PIPE)
//	{
  //  	perror("syntax error near unexpected token `|\'\n");
    //	return (NULL);
//	}
/*	if (!all_cmds)
	{
		ft_free_tokens(&head_parser);
		ft_free_cmd(new_cmd);
		ft_free_cmd(all_cmds);
		free(cmd_path);
		return (NULL);
	}*/
	//ft_free_cmd(new_cmd) hace SEVFa;
	//ft_free_tokens(&head_parser);
	//ft_free_tokens(&parser);
	return (all_cmds);
}
