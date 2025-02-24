/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:57:31 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 21:43:17 by yrodrigu         ###   ########.fr       */
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
		return (NULL);
	return (path_env);
}

static void	ft_free_case(char **path_to_exec, int *i)
{
	free(*path_to_exec);
	*path_to_exec = NULL;
	(*i)++;
}

static char	**ft_first_check(char *path, char *cmd, char ***path_dir)
{
	*path_dir = NULL;
	if (!path || !cmd)
		return (NULL);
	*path_dir = ft_split(path, ':');
	if (!*path_dir)
		return (NULL);
	return (*path_dir);
}

char	*ft_get_path(char *path, char *cmd)
{
	char	**path_dir;
	char	*path_to_exec;
	char	*tmp;
	int		i;

	path_dir = ft_first_check(path, cmd, &path_dir);
	if (!path_dir)
		return (NULL);
	i = 0;
	while (path_dir[i])
	{
		tmp = ft_strjoin(path_dir[i], "/");
		if (!tmp)
			return (ft_free_array(path_dir), NULL);
		path_to_exec = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path_to_exec)
			return (ft_free_array(path_dir), NULL);
		if (access(path_to_exec, F_OK | X_OK) == 0)
			break ;
		ft_free_case(&path_to_exec, &i);
	}
	if (!path_to_exec)
		path_to_exec = ft_strdup(cmd);
	return (ft_free_array(path_dir), path_to_exec);
}
