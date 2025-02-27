/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:48:03 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 14:41:39 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_child_hdoc(t_tokens **lexer, t_cmds *cmds,
		t_dir *redir, t_utils *utils)
{
	char	f_name[12];
	char	*stop;
	int		cmds_amount;

	ft_bzero(f_name, 12);
	ft_strlcpy(f_name, redir->filename, ft_strlen(redir->filename) + 1);
	cmds_amount = utils->cmds_amount;
	stop = ft_strtrim((*lexer)->next->value, "'\"");
	if (!stop)
	{
		ft_putstr_fd("minishell: heredoc: unexpected EOF\n", 2);
		ft_cleanup_child_hdoc(lexer, cmds, utils, redir);
		exit(EXIT_FAILURE);
	}
	ft_free_array(utils->env_in_char);
	while ((*lexer)->prev)
		*lexer = (*lexer)->prev;
	ft_cleanup_child_hdoc(lexer, cmds, utils, redir);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (ft_read_to_file(stop, cmds_amount, f_name) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	ft_fork_hdoc(t_tokens **lexer, t_cmds *cmds, t_dir *redir, t_utils *utils)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_child_hdoc(lexer, cmds, redir, utils);
	ft_wait_for_children(1, &utils->exit_status);
	if (!ft_hdoc_quotes(*lexer))
		ft_exp_hd(redir, utils);
	return (0);
}

static t_dir	*ft_init_hdoc_node(void)
{
	t_dir	*redir_node;

	redir_node = (t_dir *)malloc(sizeof(t_dir));
	if (!redir_node)
		return (NULL);
	redir_node->heredoc = 1;
	redir_node->filename = ft_random_filename();
	if (!(redir_node->filename))
		return (free (redir_node), NULL);
	return (redir_node);
}

t_dir	*ft_hdoc_redir(t_tokens **lexer, t_cmds *cmds, t_utils *utils)
{
	t_dir	*redir_node;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (cmds && cmds->error_fd)
		return (NULL);
	redir_node = ft_init_hdoc_node();
	if (!redir_node)
		return (NULL);
	if (ft_fork_hdoc(lexer, cmds, redir_node, utils) || g_signal)
		return (ft_hdoc_error_handler(redir_node, cmds));
	redir_node->fd = ft_open_fd(redir_node->filename, O_RDONLY);
	if (redir_node->fd < 0)
		return (ft_exit_redir(1, redir_node, utils));
	return (redir_node);
}
