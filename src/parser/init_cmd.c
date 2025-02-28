/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:34:24 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 15:58:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_init_cmd_node(t_cmds *node, int num)
{
	int	i;

	node->cmd_array = NULL;
	if (num > 0)
	{
		node->cmd_array = malloc((num + 1) * sizeof(char *));
		if (!node->cmd_array)
			return (-1);
		i = 0;
		while (i <= num)
		{
			node->cmd_array[i] = NULL;
			i++;
		}
	}
	node->error_fd = 0;
	node->full_path = NULL;
	node->prev = NULL;
	node->next = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	return (0);
}

char	*ft_no_path(t_cmds *node_cmd)
{
	if (!node_cmd || !node_cmd->cmd_array || !node_cmd->cmd_array[0])
		return (NULL);
	if (node_cmd->cmd_array[0][0] == '/')
		return (ft_strdup(D_ENV));
	return (NULL);
}

void	ft_set_full_path(t_cmds *node_cmd, char *path)
{
	char	*no_path;

	node_cmd->full_path = ft_get_path(path, node_cmd->cmd_array[0]);
	if (!node_cmd->full_path)
	{
		no_path = ft_no_path(node_cmd);
		if (!no_path)
			return ;
		if (no_path)
			node_cmd->full_path = ft_get_path(no_path, node_cmd->cmd_array[0]);
		free(no_path);
	}
}
