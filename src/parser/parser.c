/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/30 18:54:48 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static void	*free_cmd_array(char **cmd_array)
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
	node_cmd->prev = NULL;
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
	char *cmd_path;
	int count_tokens = 0;

    head_parser = lexer;
	parser = lexer;
	//new_cmd = NULL;
	count_tokens = 0;
	if (parser && parser->token == PIPE)
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	cmd_path = path;
	all_cmds = NULL;
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
			//return (NULL);
			return (ft_free_cmd(new_cmd), NULL);
		ft_addlast_pnode(&all_cmds, new_cmd);
    }
	else if (parser && parser->token == PIPE)
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	return (all_cmds);
}*/
// Libera un array de cadenas y devuelve NULL
static void	*free_cmd_array(char **cmd_array)
{
	int	i;

	if (!cmd_array)
		return (NULL);
	i = 0;
	while (cmd_array[i])
	{
		free(cmd_array[i]);
		cmd_array[i] = NULL;
		i++;
	}
	free(cmd_array);
	return (NULL);
}

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

// Crea un nodo de comandos y maneja errores de memoria
t_cmds *ft_create_node_cmd(t_tokens *lexer, int count_tokens, char *path)
{
	t_cmds	*node_cmd;
	int		i;

	if (!lexer || count_tokens <= 0)
		return (NULL);
	node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node_cmd)
		return (NULL);
	if (ft_init_cmd_node(node_cmd, count_tokens) == -1)
	{
		free(node_cmd);
		return (NULL);
	}
	/*node_cmd->cmd_array = (char **)malloc((count_tokens + 1) * sizeof(char *));
	if (!node_cmd->cmd_array)
		return (free(node_cmd), NULL);*/
	i = 0;
	while (lexer && lexer->token != PIPE && i < count_tokens)
	{
		node_cmd->cmd_array[i] = ft_strdup(lexer->value);
		if (!node_cmd->cmd_array[i])
			return (free_cmd_array(node_cmd->cmd_array), free(node_cmd), NULL);
		i++;
		lexer = lexer->next;
	}
	node_cmd->cmd_array[i] = NULL;
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	if (!node_cmd->full_path)
		//return (free_cmd_array(node_cmd->cmd_array), free(node_cmd), NULL);
		return (NULL);
	node_cmd->next = NULL;
	node_cmd->prev = NULL;
	return (node_cmd);
}

// Analiza los tokens y crea una lista de comandos
t_cmds *ft_parser(t_tokens *lexer, char *path)
{
	t_cmds		*all_cmds = NULL;
	t_cmds		*new_cmd;
	t_tokens	*head_parser = lexer;
	int			count_tokens = 0;

	while (lexer)
	{
		if (lexer->token == WORD)
			count_tokens++;
		else if (lexer->token == PIPE)
		{
			if (count_tokens == 0)
				return (perror("syntax error near unexpected token `|\'\n"), NULL);
			new_cmd = ft_create_node_cmd(head_parser, count_tokens, path);
			if (!new_cmd)
				return (ft_free_cmd(all_cmds), NULL);
			ft_addlast_pnode(&all_cmds, new_cmd);
			head_parser = lexer->next;
			count_tokens = 0;
		}
		lexer = lexer->next;
	}
	if (count_tokens > 0)
	{
		new_cmd = ft_create_node_cmd(head_parser, count_tokens, path);
		if (!new_cmd)
			return (ft_free_cmd(all_cmds), NULL);
		ft_addlast_pnode(&all_cmds, new_cmd);
	}
	return (all_cmds);
}
