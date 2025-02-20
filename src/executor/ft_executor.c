/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:08:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/20 08:24:06 by rbuitrag         ###   ########.fr       */
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

int	ft_forking(t_cmds *cmd, int	prev_read, int *fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_init_signals(1);
		ft_dup_close(cmd, prev_read, fd);
		execve(cmd->full_path, cmd->cmd_array, env);
	}
	return (1);
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
	int i;

	i = 0;
	while (utils->builtins[i])
	{
		if (!ft_strncmp(cmd->cmd_array[0], utils->builtins[i], ft_strlen(utils->builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exec_builtin(t_cmds *cmd, t_utils *utils, int fd)
{
	if (!ft_strncmp(cmd->cmd_array[0], "echo", 4))
		utils->exit_status = ft_echo(cmd->cmd_array, fd);
	else if(!ft_strncmp(cmd->cmd_array[0], "env", 4))
		utils->exit_status = ft_env(utils, fd);
	else if(!ft_strncmp(cmd->cmd_array[0], "pwd", 4))
		utils->exit_status = ft_pwd(utils->environ);
	else if (!ft_strncmp(cmd->cmd_array[0], "export", 6))
		utils->exit_status = ft_export(cmd, utils->environ);
	else if (!ft_strncmp(cmd->cmd_array[0], "unset", 5))
		utils->exit_status = ft_unset(cmd->cmd_array, &utils->environ);
	else if (!ft_strncmp(cmd->cmd_array[0], "cd", 2))
		utils->exit_status = ft_cd(cmd->cmd_array, utils->environ);
	else if (!ft_strncmp(cmd->cmd_array[0], "exit", 4))
		utils->exit_status = ft_exit(cmd->cmd_array, utils);
}

int	ft_verify_cmd(t_cmds *cmd, t_utils *utils)
{
	if (!ft_is_builtin(cmd, utils) && !cmd->full_path)
	{
		ft_putstr_fd("ADVICE:\nType export PATH=/usr/bin:/bin to execute the commands\n", 2);
		ft_putstr_fd(cmd->cmd_array[0], 2);
		ft_putstr_fd(": Not such a file or directory\n", 2);
		utils->exit_status = 127;
		return (1);
	}
	if (!ft_is_builtin(cmd, utils) && access(cmd->full_path, F_OK))
	{
		ft_putstr_fd(cmd->cmd_array[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		utils->exit_status = 127;
		return (1);
	}
	/*if (cmd->redir_in && cmd->redir_in->fd == -1)
		return (1);*/
	if (cmd->redir_out && isatty(cmd->redir_out->fd))
		cmd->redir_out = ft_exit_redir(2, cmd->redir_out, utils);
	return (0);
}

void	ft_call_builtin(t_cmds *cmd, t_utils *utils, int pipe)
{
	if (cmd->next)
		ft_exec_builtin(cmd, utils, pipe);
	else
		ft_exec_builtin(cmd, utils, 1);
}

void	ft_wait_for_children(int i, int *exit_status)
{
	int	exit;
	
	exit = 0;
	while (i-- > 0)
	{
		wait(&exit);
		if (WIFSIGNALED(exit))
		{
			*exit_status = 128 + WTERMSIG(exit);
			if (WTERMSIG(exit) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else if (WTERMSIG(exit) == SIGINT)
			{
				g_signal = 1;
				ft_putstr_fd("\n", 2);
			}
		}
		else if (WIFEXITED(exit))
			*exit_status = WEXITSTATUS(exit);
	}
	 
}

void	ft_executor(t_cmds *current, t_utils *utils, char **env)
{
	int	fd[2];
	int	prev_read;
	int	i;
	
	i = 0;
	prev_read = -1;
	signal(SIGINT, SIG_IGN);
	while (current)
    {
    	if (current->next && pipe(fd) == -1)
			return ;
		if (current->cmd_array && current->cmd_array[0])
		{
			if (!ft_verify_cmd(current, utils))
			{
				if (ft_is_builtin(current, utils))
					ft_call_builtin(current, utils, fd[1]);
				else
					i += ft_forking(current, prev_read, fd, env);
        	}
		}
		ft_reset_read_end(current, &prev_read, fd);
		current = current->next;
     }
	ft_wait_for_children(i, &utils->exit_status);
}
