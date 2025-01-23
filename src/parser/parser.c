/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:24:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/23 09:59:14 by rbuitrag         ###   ########.fr       */
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
	{
		free(node_cmd);
        return (NULL);
	}
    node_cmd->cmd_array = (char **)malloc((count + 1) * sizeof(char *));
    if (!node_cmd->cmd_array)
    {
        free(node_cmd->cmd_array);
        return (NULL);
    }
    i = 0;
    while (lexer && lexer->token != PIPE && i < count)
    {
        node_cmd->cmd_array[i] = ft_strdup(lexer->value);
        if (!node_cmd->cmd_array[i])
        {
            // Liberar memoria en caso de error
            while (--i >= 0)
                free(node_cmd->cmd_array[i]);
            free(node_cmd->cmd_array);
            free(node_cmd);
            return (NULL);
        }
        i++;
        lexer = lexer->next;
    }
	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	node_cmd->cmd_array[i] = NULL;
    node_cmd->next = NULL;
    return (node_cmd);
}

void print_find_cmd(t_cmds	*find_cmd)
{
	t_cmds	*print;
	int		i;

	
	if (!find_cmd)
		return ;
	print  = find_cmd;
	while (print)
	{
		i = 0;
		while (print->cmd_array[i])
		{	
			printf(GRAY "Value CMD: %s\n", print->cmd_array[i]);
			i++;
		}
		printf(RED "Path value CMD: %s\n", print->full_path);
		print = print->next;
	}
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
				// Creación del nodo de comando antes de reajustar el puntero
            	new_cmd = ft_create_node_cmd(head_parser, count_tokens, cmd_path);
            	if (!new_cmd)
                return (NULL);
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
        	return (NULL);
    	if (last_cmd)
        	last_cmd->next = new_cmd;
    	else
        	all_cmds = new_cmd;
    	}
	else if (parser && parser->token == PIPE) // PIPE al final: error de sintaxis
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	// Imprime la lista final de comandos para depuración
	//print_find_cmd(all_cmds);
	return (all_cmds);
}

/* hacer full path y redirecciones, porque ahora va creando nodos en t_cmds*/
/* pipes no al final sin nada*/
