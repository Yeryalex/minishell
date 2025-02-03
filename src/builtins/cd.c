/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:40:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/03 20:15:18 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_modify_especific_env(char *cwd, t_env *env, char *key_value)
{
	char	**container;
	char	*oldpwd;
	
	container = (char **)malloc(sizeof(char *) * 3);
	if (!container)
		return ;
	oldpwd = ft_strjoin(key_value, cwd);
	container[0] = ft_strdup("");
	container[1] = oldpwd;
	container[2] = 0;
	ft_add_node_env(container, env);
	ft_free_array(container);
}

int	ft_cd_home(t_env *env)
{
	char	cwd[1024];
	char	*home;

	home = get_value_from_env(env, "HOME");
	if (!home)
		perror("minishell : cd: HOME not set");
	if (!home)
		return (1);
	if (!getcwd(cwd, 1024))
		return (1);
	ft_modify_especific_env(cwd, env, "OLDPWD=");
	chdir(home);
	if (!getcwd(cwd, 1024))
		return (1);
	ft_modify_especific_env(cwd, env, "PWD=");
	return (0);
}

int	ft_cd(char **cmd_array, t_env *env)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
		return (1);
	if (!cmd_array[1])
		ft_cd_home(env);
	return (0);
}
