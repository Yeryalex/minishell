/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:40 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/10 09:06:05 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_file(t_dir *node)
{
	if (!node->filename)
		return (1);
	if (access(node->filename, F_OK | R_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(node->filename);
		return (1);
	}
	return (0);
}

/*void	*ft_hdoc_error_handler(t_dir *redir_node, t_cmds *parser_nodes)
{
	unlink(redir_node->filename);
	free(redir_node->filename);
	free(redir_node);
	if (g_signal == 1)
		parser_nodes->error_fd = 1;
	return (NULL);
}

t_dir	*ft_hdoc_redir(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_utils *utils)
{
	t_dir	*redir_node;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->heredoc = 1;
	redir_node->filename = ft_random_filename();
	if (ft_fork_hdoc(lexer_nodes, parser_nodes, redir_node, utils) || g_signal)
		return (hdoc_error_handler(redir_node, parser_nodes));
	redir_node->fd = open_fd(redir_node->filename, O_RDONLY);
	if (redir_node->fd < 0)
		return (exit_redir(1, redir_node, utils));
	return (redir_node);
}*/

t_dir	*ft_append_gthan_redir(char *file_name, int token, t_utils *utils, t_cmds *parser_nodes)
{
	t_dir	*redir_node;
	int		mode;

	if (parser_nodes && parser_nodes->error_fd)
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
	else if (token == GTHAN)
		redir_node->fd = ft_open_fd(redir_node->filename, mode | O_TRUNC);
	if (redir_node->fd < 0)
		return (ft_exit_redir(1, redir_node, utils));
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
	if (ft_check_file(redir_node))
		parser_nodes->error_fd = 1;
	else
		redir_node->fd = ft_open_fd(redir_node->filename, O_RDONLY);
	return (redir_node);
}
