/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expanser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:16:01 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/17 11:16:05 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/*char *ft_validate_command(char **paths, const char *command)
{
    char *full_path;
    int i = 0;

    while (paths[i])
    {
        full_path = malloc(ft_strlen(paths[i]) + ft_strlen(command) + 2);
        if (!full_path)
        {
            free (full_path);
            return (NULL);
        }
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, F_OK | X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}*/

static void ft_free_array(char **array)
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

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
				return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_paths_from_env(t_env *environ)
{
	char	**paths;
	char	*path_env;

	path_env = get_env_value(environ, "PATH");
    if (!path_env)
    {
        free(path_env);
		return (NULL);
    }
    paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
    return (path_env);
}


char    *ft_get_path(char *path, char *cmd) // full_path, cmd->cmd_array[0]
{
    char    **path_dir;
    char    *path_to_exec;
    char    *tmp;
    int     i;

    path_dir = ft_split(path, ':');
    if (!path_dir)
        return NULL;
    i = 0;
    while(path_dir[i])
    {
        path_to_exec = ft_strjoin(path_dir[i], "/");
        if (!path_to_exec)
            return (ft_free_array(path_dir), NULL);
        tmp = ft_strjoin(path_to_exec, cmd);
        if (!tmp)
            return (ft_free_array(path_dir), free(path_to_exec), NULL);
        free(path_to_exec);
        path_to_exec = tmp;
        if (access(path_to_exec, F_OK | X_OK) == 0)
            break ;
        free(path_to_exec);
        i++;
    }
    return (ft_free_array(path_dir), path_to_exec);
}

/* Lo quitare con el de Yeri es solo pruebas*/
void    execute_commands(t_cmds *cmd, char **env)
{
     if (execve(cmd->full_path, cmd->cmd_array, env) == -1)
        printf("Error in execve\n");
}
