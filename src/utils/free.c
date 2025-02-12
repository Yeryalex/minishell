/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:36:31 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 08:18:00 by rbuitrag         ###   ########.fr       */
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
	free(env);
}

void	ft_free_utils(t_utils *utils)
{
	int	i;

	i = 0;
	if (!utils)
		return;
	if (utils->builtins[i])
		while (utils->builtins[i])
			free(utils->builtins[i++]);
	if (utils->environ)
		ft_clear_lstenv(utils->environ);
	free(utils);
}
void ft_free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    while (array[i])
    {
		free(array[i]);
		array[i] = NULL;
		i++;
    }
	free(array);
}

void	ft_free_cmd(t_cmds *cmd)
{
	t_cmds 	*tmp;
	int	i;
	
	if (!cmd)
		return;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd_array)
		{
			i = 0;
			while (tmp->cmd_array[i])
			{
				free(tmp->cmd_array[i]);
				tmp->cmd_array[i] = NULL;
				i++;
			}
		}
		free(tmp->cmd_array);
		tmp->cmd_array = NULL;
	
		if (tmp->full_path)
			free(tmp->full_path);
		if (tmp->redir_in)
			ft_free_redir(tmp->redir_in);
		if (tmp->redir_out)
			ft_free_redir(tmp->redir_out);
		free(tmp);
	}	
}

