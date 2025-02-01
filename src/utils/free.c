/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:31 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/31 13:13:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_free_redir(t_dir *node)
{
	if (node)
	{
		if (node->fd >= 0)
			close (node->fd);
		//if (node->here_doc && !access(node->filename, F_OK))
		//	unlink(node->filename);
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
}

void ft_free_utils(t_utils *utils)
{
    if (!utils)
        return ;
    if (utils->environ)
		ft_free_env(utils->environ);
	//if (utils->builtins[])
	//	ft_free_array(utils->builtins);
    free(utils);
	utils = NULL;
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
	return (NULL);
}

void	ft_free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!cmd)
		return;
	while (cmd)
	{
		tmp = cmd->next;
		ft_free_one_to_cmd(cmd);
		cmd = tmp;
	}
}
