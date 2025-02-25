/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:50 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/25 12:50:47 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
void	ft_expand_line(char **line, t_utils *utils)
{
	t_exp	*exp_node;
	char	*tmp;
	int		tot_len;

	exp_node = ft_scan_expansions(*line, utils->environ, utils->exit_status);
	if (exp_node)
	{
		tot_len = ft_get_new_str_len(*line, exp_node);
		tmp = ft_expand(*line, &exp_node, tot_len);
		if (tmp)
		{
			free (*line);
			*line = tmp;
		}
	}
}
*/

void	ft_remove_newline(char **line)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
	{
		tmp = ft_substr(*line, 0, len - 1);
		free (*line);
		*line = tmp;
	}
	
}

static void	ft_expand_hdoc(t_dir *redir_node, t_utils *utils, int new_fd)
{
	char			*line;
	char			*trimmed;

	line = get_next_line(redir_node->fd);
	while (line)
	{
		ft_remove_newline(&line);
		utils->value_to_expand = line;
		trimmed = ft_check_quotes(utils);
		write(new_fd, trimmed, ft_strlen(trimmed));
		write(new_fd, "\n", 1);
		//free (line);
		line = get_next_line(redir_node->fd);
	}
	free(line);
}

static void	ft_close_fds_exp_hdoc(int new_fd, int redir_node_fd)
{
	close(new_fd);
	close(redir_node_fd);
}

void	ft_exp_hd(t_dir *redir_node, t_utils *utils)
{
	char			*new_filename;
	int				new_fd;

	new_filename = ft_random_filename();
	if (!new_filename)
		return ;
	new_fd = ft_open_fd(new_filename, O_WRONLY | O_CREAT);
	redir_node->fd = ft_open_fd(redir_node->filename, O_RDONLY);
	if (new_fd < 0 || redir_node->fd < 0)
	{
		free (new_filename);
		return ;
	}
	ft_expand_hdoc(redir_node, utils, new_fd);
	ft_close_fds_exp_hdoc(new_fd, redir_node->fd);
	unlink(redir_node->filename);
	free (redir_node->filename);
	redir_node->filename = new_filename;
}
