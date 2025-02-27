
#include "../../inc/minishell.h"

int	ft_open_fd(char *filename, int mode)
{
	int	fd;

	if (mode & O_CREAT)
		fd = open(filename, mode, 0664);
	else
		fd = open(filename, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	ft_check_file(t_dir *node, t_utils *utils)
{
	if (!node->filename)
		return (1);
	if (access(node->filename, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		utils->redir_error = 1;
		return (1);
	}
	if (access(node->filename, R_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);	
		ft_putstr_fd(node->filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		utils->redir_error = 1;
		return (2);
	}
	return (0);
}

void	*ft_exit_redir(int error, t_dir *redir_node, t_utils *utils)
{
	if (!redir_node)
		return (NULL);
	if (redir_node->filename)
		free (redir_node->filename);
	if (redir_node->fd >= 0 && redir_node->fd <= 42)
		close (redir_node->fd);
	free (redir_node);
	if (error == 1)
		utils->exit_status = 2;
	else if (error == 3)
		utils->exit_status = 3;
	return (NULL);
}

t_dir	*ft_append_gthan_redir(char *file_name, int token, t_utils *utils, t_cmds *parser_nodes)
{
	t_dir	*redir_node;
	int		mode;

	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	if(utils->redir_error)
		return (NULL);
	redir_node = (t_dir *)malloc(sizeof(t_dir));
	if (!redir_node)
		return (NULL);
	redir_node->heredoc = 0;
	redir_node->filename = ft_strdup(file_name);
	if (!redir_node->filename)
		return (ft_exit_redir(3, redir_node, NULL));
	mode = (O_WRONLY | O_CREAT);
	if (token == APPEND)
		redir_node->fd = ft_open_fd(redir_node->filename, mode | O_APPEND);
	if (token == GTHAN)
		redir_node->fd = ft_open_fd(redir_node->filename, mode | O_TRUNC);
	if (redir_node->fd < 0)
		return (ft_exit_redir(1, redir_node, utils));
	if (redir_node == NULL)
		utils->redir_error = 1;
	return (redir_node);
}

t_dir	*ft_sthan_redir(char *file_name, t_utils *utils, t_cmds *parser_nodes)
{
	t_dir	*redir_node;

	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_dir *)malloc(sizeof(t_dir));
	if (!redir_node)
		return (NULL);
	redir_node->heredoc = 0;
	redir_node->filename = ft_strdup(file_name);
	redir_node->fd = -1;
	if (!redir_node->filename)
		return (ft_exit_redir(3, redir_node, utils));
	if (ft_check_file(redir_node, utils))
	{
		utils->redir_error = 1;
		//ft_free_redir(redir_node);
		return (redir_node);
	}
	else
		redir_node->fd = ft_open_fd(redir_node->filename, O_RDONLY);
	if (redir_node == NULL)
		utils->redir_error = 1;
	return (redir_node);
}