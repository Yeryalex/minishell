#include "../../inc/minishell.h"

static t_redir	*ft_fill_redirections(t_tokens **lexer, t_cmd *cmds, t_utils *utils)
{
	t_redir		*new_node;

	new_node = NULL;
	if (!(*lexer)->next || (*lexer)->next->token != WORD)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		utils->exit_status = 2;
		return (NULL);
	}
	if ((*lexer)->token == H_DOC)
		new_node = hdoc_redir(lexer, cmds, utils);
	else if ((*lexer)->token == STHAN)
		new_node = sthan_redir((*lexer)->next->value, utils, cmds);
	else if ((*lexer)->token == APPEND || (*lexer)->token == GTHAN)
		new_node = append_gthan_redir((*lexer)->next->value, (*lexer)->token, utils, cmds);
	return (new_node);
}

void	gthan_append_cmds(t_tokens **lexer, t_cmd *cmds)
{
	if (cmds->redir_out)
		cmds->redir_out = ft_free_redir(cmds->redir_out);
	cmds->redir_out = ft_fill_redirections(lexer, cmds, NULL);
}

void	sthan_hdoc_cmds(t_tokens **lexer, t_cmd *cmds, t_utils *utils)
{
	if (cmds->redir_in)
		cmds->redir_in = ft_free_redir(cmds->redir_in);
	cmds->redir_in = ft_fill_redirections(lexer, cmds, utils);
}