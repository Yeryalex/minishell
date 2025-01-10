#include "../../inc/minishell.h"

t_cmds *ft_create_node_cmd(t_tokens *lexer, int count)
{
    t_cmds *node_cmd;
    int i;

    if (!lexer || count <= 0)
        return (NULL);

    node_cmd = (t_cmds *)malloc(sizeof(t_cmds));
    if (!node_cmd)
        return (NULL);

    node_cmd->cmd_array = (char **)malloc((count + 1) * sizeof(char *));
    if (!node_cmd->cmd_array)
    {
        free(node_cmd);
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
        printf("cmd values %s posicion %d\n", node_cmd->cmd_array[i], i);
        i++;
        lexer = lexer->next;
    }

    node_cmd->cmd_array[i] = NULL; // Finaliza el array de comandos
    node_cmd->next = NULL; // Inicializa siguiente nodo como NULL
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
		print = print->next;
	}
}

t_cmds *ft_parser(t_tokens *lexer)
{
    t_cmds *all_cmds;
    t_cmds *last_cmd;
	t_cmds *new_cmd;
    t_tokens *head_parser; 
    t_tokens *parser;
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
	while (parser)
	{
    	if (parser->token == WORD)
    	   	count_tokens++;  // Aumenta el contador cuando se encuentra un token de tipo WORD
    	else if (parser->token == PIPE)
    	{
        	if (count_tokens > 0)
        	{
            	// Creación del nodo de comando antes de reajustar el puntero
            	new_cmd = ft_create_node_cmd(head_parser, count_tokens);
            	if (!new_cmd)
                return (NULL);
            	printf("Nuevo nodo de comando creado: %s\n", new_cmd->cmd_array[0]);
               	if (last_cmd)  // Si ya hay un nodo anterior, lo enlazamos con el nuevo
                	last_cmd->next = new_cmd;
            	else
                	all_cmds = new_cmd;  // Si es el primer nodo, lo asignamos como inicio de la lista
            	last_cmd = new_cmd;  // Actualizamos last_cmd para el próximo nodo
        	}
			else
        	{
            	// PIPE sin tokens antes: error de sintaxis
            	perror("syntax error near unexpected token `|\'\n");
            	return (NULL);
        	}
           	// Reajusta el puntero a los tokens después del PIPE
        	head_parser = parser->next;
        	count_tokens = 0;  // Reinicia el contador de tokens para el siguiente comando
    	}
    	parser = parser->next;  // Avanza al siguiente token
	}
	// Después de terminar, aseguramos que los tokens restantes se procesen
	if (count_tokens > 0)  // Si hay tokens pendientes para procesar, se crea un nodo
	{
    	new_cmd = ft_create_node_cmd(head_parser, count_tokens);
    	if (!new_cmd)
        	return (NULL);
    	if (last_cmd)
        	last_cmd->next = new_cmd;
    	else
        	all_cmds = new_cmd;  // Si es el primer nodo, lo asignamos como inicio de la lista
    	printf("Nuevo nodo de comando creado al final: %s\n", new_cmd->cmd_array[0]);
	}
	else if (parser && parser->token == PIPE) // PIPE al final: error de sintaxis
	{
    	perror("syntax error near unexpected token `|\'\n");
    	return (NULL);
	}
	// Imprime la lista final de comandos para depuración
	print_find_cmd(all_cmds);
	return (all_cmds);
}

/* hacer full path y redirecciones, porque ahora va creando nodos en t_cmds*/
/* pipes no al final sin nada*/
