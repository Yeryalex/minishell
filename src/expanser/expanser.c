/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:39 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/17 11:32:00 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_env_value(t_env *envs, char *key_value)
{
	while (envs)
    {
        if (strcmp(envs->key, key_value) == 0)
            return envs->value;
        envs = envs->next;
    }
    return NULL;
}

t_cmds *ft_expand_tokens(t_tokens *tokens, t_env *env)
{
    t_cmds *head = NULL;
    t_cmds *current = NULL;
    t_cmds *new_cmd = NULL;
    char *path_value;
    char **paths;
    char *command_path;
	int	i;

    path_value = get_env_value(env, "PATH");
    if (!path_value)
        return (NULL);

    paths = ft_split_path(path_value);
    if (!paths)
        return (NULL);

    while (tokens)
    {
        new_cmd = (t_cmds *)malloc(sizeof(t_cmds));
        if (!new_cmd)
            return (NULL);

        command_path = ft_validate_command(paths, tokens->value);
        if (command_path)
        {
            new_cmd->cmd_array = (char **)malloc(2 * sizeof(char *));
            new_cmd->cmd_array[0] = ft_strdup(command_path);
            new_cmd->cmd_array[1] = NULL;
            new_cmd->next = NULL;

            if (!head)
                head = new_cmd;
            else
                current->next = new_cmd;

            current = new_cmd;
            free(command_path);
        }
        tokens = tokens->next;
    }
   i = 0;
   while (paths[i])
    {
		free(paths[i]);
		i++;
	}
    free(paths);

    return (head);
}
