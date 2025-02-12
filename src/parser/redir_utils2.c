/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:04:58 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 13:09:28 by rbuitrag         ###   ########.fr       */
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
	if (redir_node->fd >= 0 && redir_node->fd <= 42)
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

void	ft_child_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, 	t_dir *redir_node, t_utils *utils)
{
	char	*stop;
	int		cmds_amount;
	char	f_name[15];

	ft_bzero(f_name, 15);
	ft_strlcpy(f_name, redir_node->filename,
		ft_strlen(redir_node->filename) + 1);
	cmds_amount = utils->cmds_amount;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	stop = ft_strdup((*lexer_nodes)->next->value);
	ft_free_child_hdoc(lexer_nodes, parser_nodes, utils);
	free (redir_node->filename);
	free (redir_node);
	if (ft_read_to_file(stop, cmds_amount, f_name) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	ft_fork_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_dir *redir_node, t_utils *utils)
{
	pid_t	pid;
	char	*n_stop;
	int		expand;

	expand = 1;
	pid = fork();
	if (pid == -1)
		return (1);
	n_stop = ft_remove_quotes((*lexer_nodes)->next->value);
	if (n_stop != (*lexer_nodes)->next->value)
	{
		free ((*lexer_nodes)->next->value);
		(*lexer_nodes)->next->value = n_stop;
		expand = 0;
	}
	if (pid == 0)
		ft_child_hdoc(lexer_nodes, parser_nodes, redir_node, utils);
	ft_wait_for_childs(1, &utils->exit_status);
	//if (expand)
	//	ft_exp_hd(redir_node, utils);
	return (0);
}