/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:48:03 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/25 21:01:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	*ft_hdoc_error_handler(t_dir *redir_node, t_cmds *parser_nodes)
{
	unlink(redir_node->filename);
	free(redir_node->filename);
	free(redir_node);
	if (parser_nodes)
		parser_nodes->error_fd = 1;
	return (NULL);
}

static void	ft_free_child_hdoc(t_tokens **lexer, t_cmds *cmds)
{
    ft_free_tokens(lexer);
    ft_free_cmd(cmds);
}

void	ft_child_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_dir *redir_node, t_utils *utils)
{
	char	*stop;
	int		cmds_amount;
	char	f_name[1096];

	ft_bzero(f_name, ft_strlen(redir_node->filename) + 1);
	ft_strlcpy(f_name, redir_node->filename, ft_strlen(redir_node->filename) + 1);
	cmds_amount = utils->cmds_amount;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	stop = ft_strdup((*lexer_nodes)->next->value);
	ft_clear_lstenv(utils->environ);
	free(utils);
	ft_free_child_hdoc(lexer_nodes, parser_nodes);
	free(redir_node->filename);
	free(redir_node);
	if (ft_read_to_file(stop, cmds_amount, f_name) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	ft_fork_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_dir *redir_node, t_utils *utils)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{	
		ft_init_signals(1);
		ft_child_hdoc(lexer_nodes, parser_nodes, redir_node, utils);
	}
	ft_wait_for_children(1, &utils->exit_status);
	ft_exp_hd(redir_node, utils);
	return (0);
}

t_dir	*ft_hdoc_redir(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_utils *utils)
{
	t_dir	*redir_node;

	redir_node = NULL;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (parser_nodes && parser_nodes->error_fd)
		return (NULL);
	redir_node = (t_dir *)malloc(sizeof(t_dir));
	if (!redir_node)
		return (NULL);
	redir_node->heredoc = 1;
	redir_node->filename = ft_random_filename();
	if (!(redir_node->filename))
		return(NULL);
	if (ft_fork_hdoc(lexer_nodes, parser_nodes, redir_node, utils) || g_signal)
		return (ft_hdoc_error_handler(redir_node, parser_nodes));
	redir_node->fd = ft_open_fd(redir_node->filename, O_RDONLY);
	if (redir_node->fd < 0)
		return (ft_exit_redir(1, redir_node, utils));
	return (redir_node);
}
