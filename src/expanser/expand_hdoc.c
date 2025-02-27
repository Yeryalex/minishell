/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:50 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 16:20:42 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void	ft_remove_newline(char **line)
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

char	*ft_expand_line(int *i, int *j, t_utils *utils)
{
	char	*temp_str;
	char	*str_value;

	str_value = utils->value_to_expand;
	temp_str = (char *)malloc(ft_strlen(str_value) + 1000);
	if (!temp_str)
		return (NULL);
	utils->temp_str = temp_str;
	while (str_value[*i])
	{
		if (str_value[*i] == '$')
			ft_expand_with_quotes(i, j, utils);
		else
			temp_str[(*j)++] = str_value[(*i)++];
	}
	temp_str[*j] = '\0';
	return (free(str_value), temp_str);
}

static void	ft_expand_hdoc(t_dir *redir_node, t_utils *utils, int new_fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(redir_node->fd);
	while (line)
	{
		ft_remove_newline(&line);
		utils->value_to_expand = line;
		trimmed = ft_quotes_in_hdoc(utils);
		write(new_fd, trimmed, ft_strlen(trimmed));
		write(new_fd, "\n", 1);
		free(trimmed);
		line = get_next_line(redir_node->fd);
	}
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
	close(new_fd);
	close(redir_node->fd);
	unlink(redir_node->filename);
	free (redir_node->filename);
	redir_node->filename = new_filename;
}
