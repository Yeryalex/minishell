#include "../../inc/minishell.h"

void print_find_cmd(t_cmds	*find_cmd)
{
	t_cmds	*print;

	print  = find_cmd;
	while (print)
	{
	//	printf(GRAY "Value CMD: %s\n", (print)->cmd);
		print = print->next;
	}
}

t_cmds	*ft_parser(t_tokens *lexer)
{

	t_cmds		*all_cmds;
	t_tokens	*parser;
	// t_tokens	*find_cmd;

	parser = lexer;
	all_cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!all_cmds)
		return (NULL);
	//all_cmds = NULL;
	// find_cmd = NULL;
	while (parser)
	{
		if ((parser->token != 1))
		{
			all_cmd->cmd = parser->value;
			all_cmds = all_cmds->next;
		}
		else 
			break;
			// find_cmd  = parser;
		parser = parser->next;
	}
	printf("New structure command %s", all_cmds->cmd[0]);
	//print_find_cmd(all_cmds);
	return (all_cmds);
}