#include "../../inc/minishell.h"

t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count)
{
	t_cmds	*node_cmd;
	int		i;

	node_cmd = NULL;
	node_cmd->cmd_array = (char **)malloc((count +1) * sizeof(char *));
	i = 0;
	if (!node_cmd)
	{
		return (NULL);
		free (node_cmd);
	}
	while (lexer && ft_strncmp(lexer->value, "|", 1) != 0 )
	{
		node_cmd->cmd_array[i] = ft_strdup(lexer->value);
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
		while (print->cmd_array[i])
		{	printf(GRAY "Value CMD: %s\n", print->cmd_array[i]);
			i++;
		}
		print = print->next;
	}
}

t_cmds	*ft_parser(t_tokens *lexer)
{

	t_cmds		*all_cmds;
	t_cmds		*head_cmd;
	t_tokens	*parser;
	int			count_tokens;

	parser = lexer;
	count_tokens = 0;
	all_cmds = NULL;
	head_cmd = NULL;
	while (parser)
	{
		if ((parser->token = 6))
 			count_tokens++;
		if ((parser->token = 1))
		parser = parser->next;
	}
	all_cmds = ft_create_node_cmd(parser, count_tokens);
//	printf("New structure command %s", all_cmds->cmd_array[0]);
// Tengo que poner all_cmd al inicio ahora mismo antes de printar esta en NULL y claro no hace nada en print_find
	print_find_cmd(all_cmds);
	return (all_cmds);
}