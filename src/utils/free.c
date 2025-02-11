/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:31 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 09:26:57 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_free_redir(t_dir *node)
{
	if (node)
	{
		if (node->fd >= 0)
			close (node->fd);
		if (node->heredoc && !access(node->filename, F_OK))
			unlink(node->filename);
		free (node->filename);
		free (node);
		node = NULL;
	}
	return (NULL);
}

void ft_free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
		tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
	//free(env);
}

void ft_free_utils(t_utils *utils)
{
    int i = 0;

    if (utils)
    {
        if (utils->environ)
		{
            ft_clear_lstenv(utils->environ);
			utils->environ = NULL;
		}
		while (i < 8)
        {
            if (utils->builtins[i])
            {
                free(utils->builtins[i]);
                utils->builtins[i] = NULL;
            }
            i++;
        }
        free(utils);
	}
}

void ft_free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    while (array[i])
    {
		free(array[i]);
		i++;
    }
	free(array);
}

void	*ft_free_one_to_cmd(t_cmds *cmd)
{
	if (cmd->cmd_array)
	{
		ft_free_array(cmd->cmd_array);
		cmd->cmd_array = NULL;
	}
	if (cmd->full_path)
	{
		free (cmd->full_path);
		cmd->full_path = NULL;
	}
	if (cmd->redir_in)
	{
		ft_free_redir(cmd->redir_in);
		cmd->redir_in = NULL;
	}
	if (cmd->redir_out)
	{
		ft_free_redir(cmd->redir_out);
		cmd->redir_out = NULL;
	}
	free(cmd);
	return (0);
}

void	ft_free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!cmd)
		return;
	tmp = NULL;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free_one_to_cmd(tmp);		
	}
}
