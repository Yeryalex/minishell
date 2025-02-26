/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:38:56 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 11:45:34 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_dup_close(t_cmds *cmd, int prev_read, int *fd)
{
	if (cmd->prev)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->redir_in)
	{
		dup2(cmd->redir_in->fd, STDIN_FILENO);
		close(cmd->redir_in->fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->redir_out)
	{
		dup2(cmd->redir_out->fd, STDOUT_FILENO);
		close(cmd->redir_out->fd);
	}
}

void	ft_reset_read_end(t_cmds *current, int *prev_read, int *fd)
{
	if (current->redir_in && current->redir_in->fd > 0)
		close(current->redir_in->fd);
	if (current->redir_out && current->redir_out->fd > 0)
		close(current->redir_out->fd);
	if (current->next)
		close(fd[1]);
	if (current->prev)
		close(*prev_read);
	if (current && current->next)
		*prev_read = fd[0];
}

int	ft_is_builtin(t_cmds *cmd, t_utils *utils)
{
	int	i;

	i = 0;
	while (utils->builtins[i])
	{
		if (!ft_strncmp(cmd->cmd_array[0], utils->builtins[i],
				ft_strlen(utils->builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

void	ft_call_builtin(t_cmds *cmd, t_utils *utils, int pipe)
{
	if (cmd->next)
		ft_exec_builtin(cmd, utils, pipe);
	else
		ft_exec_builtin(cmd, utils, 1);
}
