/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:31 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/27 12:11:58 by rbuitrag         ###   ########.fr       */
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

void *ft_free_utils(t_utils *utils)
{
    if (!utils)
        return NULL;

    if (utils->environ)
        ft_free_env(utils->environ);

    free(utils);
	return (NULL);
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
	int		i;

	if (cmd->cmd_array)
	{
		i = 0;
		while (cmd->cmd_array[i])
		{
			free (cmd->cmd_array[i]);
			cmd->cmd_array[i] = NULL;
			i++;
		}
		free(cmd->cmd_array);
	}
	if (cmd->full_path)
		free (cmd->full_path);
	if (cmd->redir_in)
		cmd->redir_in = ft_free_redir(cmd->redir_in);
	if (cmd->redir_out)
		cmd->redir_out = ft_free_redir(cmd->redir_out);
	free(cmd);
	return (NULL);
}

void	ft_free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		ft_free_one_to_cmd(cmd);
		cmd = tmp;
	}
}
