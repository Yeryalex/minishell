/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/06 11:05:01 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_child_hdoc(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	ft_free_tokens(lexer);
	ft_free_cmd(cmds);
	if(ft_clear_lstenv(utils->environ) == 0)
	    return;
	free (utils);
}

void	*ft_exit_redir(int error, t_dir *redir_node, t_utils *utils)
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
