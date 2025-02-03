/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:40:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/03 20:52:47 by yrodrigu         ###   ########.fr       */
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
		perror("minishell : cd: HOME not set\n");
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

int	ft_cd_minus(char **cmd_array, t_env *env)
{
	char	cwd[1024];
	char	*OLDPWD;

	if (cmd_array[1][1])
	{
		printf("minishell: cd: -%c: invalid option\n", cmd_array[1][1]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		return (1);
	}
	else
	{
		if (!getcwd(cwd, 1024))
			return (1);
		OLDPWD = get_value_from_env(env, "OLDPWD");
/*		if (!OLDPWD)
			perror("minishell : cd: OLDPWD not set\n");
		if (!OLDPWD)
			return (1);
*/		ft_modify_especific_env(cwd, env, "OLDPWD=");
		chdir(OLDPWD);
		if (!getcwd(cwd, 1024))
			return (1);
		ft_modify_especific_env(cwd, env, "PWD=");
	}
	return (0);
}

int	ft_calling_cd(char **cmd_array, t_env *env)
{
	if (cmd_array[1][0] == '-')
		ft_cd_minus(cmd_array, env);
	return (0);
}

int	ft_cd(char **cmd_array, t_env *env)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
		return (1);
	if (!cmd_array[1])
		ft_cd_home(env);
	else if (cmd_array[1])
		ft_calling_cd(cmd_array, env);
	return (0);
}
