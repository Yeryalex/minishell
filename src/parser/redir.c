
#include "../../inc/minishell.h"

static t_dir	*ft_fill_redirections(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	t_dir		*new_node;

	new_node = NULL;
	//if (!(*lexer)->next || (*lexer)->next->token != WORD)
	if (!lexer || !(*lexer) || !(*lexer)->next || (*lexer)->next->token != WORD)
	{
		ft_putstr_fd("minishell: syntax error con la PIPE \n", 2);
		utils->exit_status = 0;
		return (NULL);
	}
	if ((*lexer)->token == STHAN)
		new_node = ft_sthan_redir((*lexer)->next->value, utils, cmds);
	else if ((*lexer)->token == APPEND || (*lexer)->token == GTHAN)
		new_node = ft_append_gthan_redir((*lexer)->next->value, (*lexer)->token, utils, cmds);
	else if ((*lexer)->token == H_DOC)
		new_node = ft_hdoc_redir(lexer, cmds, utils);
	return (new_node);
}

int	ft_gthan_append_cmds(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	if (cmds->redir_out)
		cmds->redir_out = ft_free_redir(cmds->redir_out);
	cmds->redir_out = ft_fill_redirections(lexer, cmds, utils);
	if (!cmds->redir_out)
		return (-1);
	return (0);
}

int	ft_sthan_hdoc_cmds(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	if (cmds->redir_in)
		cmds->redir_in = ft_free_redir(cmds->redir_in);
	cmds->redir_in = ft_fill_redirections(lexer, cmds, utils);
	if (!cmds->redir_in)
		return (-1);
	return (0);
}