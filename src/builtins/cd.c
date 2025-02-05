/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:40:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/05 10:13:27 by yrodrigu         ###   ########.fr       */
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
	char	*path;

	home = get_value_from_env(env, "HOME");
	if (!home)
		perror("minishell : cd: HOME not set\n");
	if (!home)
		return (1);
	if (!getcwd(cwd, 1024))
	{
		perror("hola");
		path = get_value_from_env(env, "PWD");
		ft_modify_especific_env(path, env, "OLDPWD=");
	}
	else
		ft_modify_especific_env(cwd, env, "OLDPWD=");
	chdir(home);
	if (!getcwd(cwd, 1024))
		perror("hola\n");
	ft_modify_especific_env(cwd, env, "PWD=");
	return (0);
}

int	ft_cd_minus(char **cmd_array, t_env *env)
{
	char	cwd[1024];
	char	*oldpwd;
	char	*pwd;

	(void)cmd_array;
	if (!getcwd(cwd, 1024))
		return (1);
	oldpwd = get_value_from_env(env, "OLDPWD");
	if (!oldpwd)
		perror("minishell : cd: OLDPWD not set\n");
	if (!oldpwd)
		return (1);
	if (chdir(oldpwd))
		printf("minishell: cd: %s: No such file or directory\n", oldpwd);
	else
	{
		ft_modify_especific_env(oldpwd, env, "PWD=");
		ft_modify_especific_env(cwd, env, "OLDPWD=");
		pwd = get_value_from_env(env, "PWD");
		printf("%s\n", pwd);
	}
	return (0);
}

int	ft_change_dir(char *path, t_env *env)
{
	char	cwd[1024];
	char	*pwd;
	char	*oldpwd;

	if (!getcwd(cwd, 1024))
	{
		oldpwd = get_value_from_env(env, "OLDPWD");
		pwd = get_value_from_env(env, "PWD");
		ft_modify_especific_env(pwd, env, "OLDPWD=");
	}
	else
		ft_modify_especific_env(cwd, env, "OLDPWD=");
	if (chdir(path))
		printf("bash: cd: %s: No such file or directory\n", path);
	if (!getcwd(cwd, 1024))
	{
		printf("cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
		pwd = get_value_from_env(env, "PWD");
		path = ft_strjoin("/", path);
		ft_modify_especific_env(ft_strjoin(pwd, path), env, "PWD=");
	}
	else
		ft_modify_especific_env(cwd, env, "PWD=");
	return (0);
}

int	ft_cd(char **cmd_array, t_env *env)
{
	if (!cmd_array[1])
		ft_cd_home(env);
	else if (cmd_array[2])
		perror("minishell: cd: too many arguments\n");
	else if (cmd_array[1][0] == '-')
	{
		if (cmd_array[1][1])
		{
			printf("minishell: cd: -%c: invalid option\n", cmd_array[1][1]);
			printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
			return (1);
		}
		ft_cd_minus(cmd_array, env);
	}
	else if (cmd_array[1])
		ft_change_dir(cmd_array[1], env);
	return (0);
}
