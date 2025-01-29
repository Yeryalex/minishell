/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expanser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:16:01 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/29 12:36:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	char	*path_env;

	path_env = get_env_value(environ, "PATH");
    if (!path_env)
		return (free(path_env), NULL);
    return (path_env);
}

char    *ft_get_path(char *path, char *cmd)
{
    char    **path_dir;
    char    *path_to_exec;
    char    *tmp;
    int     i;

    if (!path || !cmd)
        return (NULL);
    path_dir = ft_split(path, ':');
    if (!path_dir)
        return (ft_free_array(path_dir), NULL);
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
		path_to_exec = NULL;
        i++;
    }
	if (!path_to_exec)
		path_to_exec  = cmd;
    return (ft_free_array(path_dir), path_to_exec);
}
