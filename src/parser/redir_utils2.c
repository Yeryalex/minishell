#include "../../inc/minishell.h"

void	free_child_hdoc(t_tokens **lexer, t_cmd *cmds, t_utils *utils)
{
	ft_free_tokens(&lexer);
	ft_free_cmd(cmds);
	if(ft_clear_lstenv(utils->envs) == 0)
	    return;
	free (utils);
}

void	*exit_redir(int error, t_redir *redir_node, t_utils *utils)
{
	if (!redir_node)
		return (NULL);
	if (redir_node->filename)
		free (redir_node->filename);
	if (redir_node->fd >= 0 && redir_node->fd <= 100)
		close (redir_node->fd);
	free (redir_node);
	if (error == 1)
		utils->exit_status = 2;
	else if (error == 3)
		utils->exit_status = 3;
	return (NULL);
}

int	open_fd(char *file_name, int mode)
{
	int	fd;

	if (mode & O_CREAT)
		fd = open(file_name, mode, 0664);
	else
		fd = open(file_name, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}