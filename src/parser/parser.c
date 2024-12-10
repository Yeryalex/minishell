#include "../../inc/minishell.h"

t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count)
{
	t_cmds	*node_cmd;
	int		i;
	//int		j;
	//int		k;
	//char 	*temp;
	//char	**spliter;
	
	if (!lexer)
		return (NULL);
	node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node_cmd)
	{
		return (NULL);
		free(node_cmd);
	}
	node_cmd->cmd_array = (char **)malloc((count + 1 ) * sizeof(char *));
	if (!node_cmd->cmd_array)
	{
		free (node_cmd);
		free (node_cmd->cmd_array);
		return (NULL);
	}
	i = 0;
	while (lexer)
	{
		if(lexer->token != PIPE)
		{
			node_cmd->cmd_array[i] = ft_strdup(lexer->value);
			if (!node_cmd->cmd_array[i])
			{
				free (node_cmd);
				free (node_cmd->cmd_array);
				return (NULL);
			}
			printf("cmd values %s posicion %d \n", node_cmd->cmd_array[i], i);
			i++;
		}
		else
			i = 0;
		lexer = lexer->next;
	}
	/*
	//De otra forma no pilla todas las WORDS antes de PIPE
	lexer = lexer->next;
	i++;
	// por ejemplo si pilla una redireccion me mete >> fichero.txt sin la >> (ya que esta al final) luego lo procesa pero no lee el final
	while (lexer) 
	{
		if(lexer->token != PIPE)
		{
			// pasar primer nodo con strdup, pero a partir del 1, unir con strjoin para hacer el nodo completo 
			temp = (char *)ft_strjoin(node_cmd->cmd_array[i - 1], lexer->value); // ls -a
			if (!temp)
			{
				free(temp);
				return (NULL);
			}
			//free(node_cmd->cmd_array[i - 1]);
			node_cmd->cmd_array[i - 1] = temp;
			node_cmd->cmd_array[i] = ((char *)ft_split(temp, '-'));
			if (!node_cmd->cmd_array[i])
			{
				free (node_cmd);
				free (node_cmd->cmd_array);
				return (NULL);
			}
			//Splitear para que el nodo tenga en posicion 0 comando y luego las flags que con - la reconoces
			spliter = ft_split(node_cmd->cmd_array[i], '-');
			k = 0;
			while (spliter[k] != NULL)
			{
				node_cmd->cmd_array[k] = ft_strdup(spliter[k]);
				if (!node_cmd->cmd_array[k])
				{
					free (node_cmd);
					free (node_cmd->cmd_array);
					return (NULL);
				}
				//spliter = (char *) ft_split(NULL, '-');
				k++;
			}*/
			node_cmd->cmd_array[i] = NULL;
			/* Hay que liberar memoria de splitter a continuacion
			j = 0;
			while (spliter[j] != NULL)
				free(spliter[j++]);
			free(spliter);
		}
		lexer = lexer->next;
		i++;
	}*/
	node_cmd->cmd_array = NULL;
	node_cmd->next = NULL;
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
		while (print->cmd_array[i])
		{	
			printf(GRAY "Value CMD: %s\n", print->cmd_array[i]);
			i++;
		}
		print = print->next;
	}
}

t_cmds	*ft_parser(t_tokens *lexer)
{

	t_cmds		*all_cmds;
	//t_cmds		*head_cmds;
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
			head_parser = parser->next;
			count_tokens = 0;
			
		}
		parser = parser->next;
	}
// Tengo que poner all_cmd al inicio ahora mismo antes de printar esta en NULL y claro no hace nada en print_find
	print_find_cmd(all_cmds);
	return (all_cmds);
}

/* hacer full path y redirecciones, porque ahora va creando nodos en t_cmds*/
/* controlar que PIPE no esta al inicio y no al final sin nada*/