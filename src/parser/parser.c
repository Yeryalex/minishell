#include "../../inc/minishell.h"

t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count)
{
	t_cmds	*node_cmd;
	int		i;

	node_cmd = NULL;
	node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node_cmd)
		return (NULL);
	i = 0;
	node_cmd->cmd_array = (char **)malloc((count + 1 ) * sizeof(char *));
	if (!node_cmd->cmd_array)
	{
		return (NULL);
		free (node_cmd);
	}
	while (lexer && (lexer->token != 1))
	{
		// pasar primer nodo con strdup, pero a partir del 1, unir con strjoin para hacer el nodo completo 
		node_cmd->cmd_array[i] = ft_strdup(lexer->value);
		printf("cmd values %s posicion %d \n", node_cmd->cmd_array[i], i);
		if (!node_cmd->cmd_array[i])
		{
			free(node_cmd);
			return (NULL);
		}
		lexer = lexer->next;
		i++;
	}
	node_cmd->cmd_array[i] = NULL;
	return (node_cmd);
}

void print_find_cmd(t_cmds	*find_cmd)
{
	t_cmds	*print;
	int		i;

	print  = find_cmd;
	while (print)
	{
		i = 0;
		while (print->cmd_array)
		{	printf(GRAY "Value CMD: %s\n", print->cmd_array);
			i++;
		}
		print = print->next;
	}
}

t_cmds	*ft_parser(t_tokens *lexer)
{

	t_cmds		*all_cmds;
	t_cmds		*head_cmds;
	t_tokens	*head_parser;
	t_tokens	*parser;
	int			count_tokens;

	parser = lexer;
	count_tokens = 0;
	all_cmds = NULL;
	head_parser = lexer;
	while (parser)
	{
		if (parser->token == WORD)
 			count_tokens++;
		else if (parser->token == PIPE)
		{
			all_cmds = ft_create_node_cmd(head_parser, count_tokens);
			//head_parser = parser->next;
			count_tokens = 0;
			
		}
		parser = parser->next;
	}
// Tengo que poner all_cmd al inicio ahora mismo antes de printar esta en NULL y claro no hace nada en print_find
	print_find_cmd(all_cmds);
	return (all_cmds);
}

/* hacer full path y redirecciones, porque ahora va creando nodos en t_cmds*/