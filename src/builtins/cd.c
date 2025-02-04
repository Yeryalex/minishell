/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:40:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/04 17:13:18 by yrodrigu         ###   ########.fr       */
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
	char	*PWD;

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
		if (!OLDPWD)
			perror("minishell : cd: OLDPWD not set\n");
		if (!OLDPWD)
			return (1);
		chdir(OLDPWD);
		ft_modify_especific_env(OLDPWD, env, "PWD=");
		ft_modify_especific_env(cwd, env, "OLDPWD=");
		PWD = get_value_from_env(env, "PWD");
		printf("%s\n", PWD);
	}
	return (0);
}

int	ft_change_dir(char *path, t_env *env)
{
	char	cwd[1024];
	char	*PWD;
	char	*OLDPWD;

	if (!getcwd(cwd, 1024))
	{
		 OLDPWD = get_value_from_env(env, "OLDPWD");
		 PWD = get_value_from_env(env, "PWD");
        ft_modify_especific_env(PWD, env, "OLDPWD=");
	}
	else
		ft_modify_especific_env(cwd, env, "OLDPWD=");

	if (chdir(path))
	{
		printf("bash: cd: %s: No such file or directory\n", path);
	}
	if (!getcwd(cwd, 1024))
	{
		perror("cd: error retrieving current directory: getcwd: ");
		perror("cannot access parent directories: No such file or directory");
    	PWD = get_value_from_env(env, "PWD");
		path = ft_strjoin("/", path);
		ft_modify_especific_env(ft_strjoin(PWD, path), env, "PWD=");
	}
	else
	{
		ft_modify_especific_env(cwd, env, "PWD=");
	}
	return (0);
}

int	ft_calling_cd(char **cmd_array, t_env *env)
{
	if (cmd_array[1][0] == '-')
		ft_cd_minus(cmd_array, env);
	else if (cmd_array[1])
		ft_change_dir(cmd_array[1], env);
	return (0);
}

int	ft_cd(char **cmd_array, t_env *env)
{
	if (!cmd_array[1])
		ft_cd_home(env);
	else if (cmd_array[2])
		perror("minishell: cd: too many arguments\n");
	else if (cmd_array[1])
		ft_calling_cd(cmd_array, env);
	return (0);
}



/*
char    *ft_get_path(char *path, char *cmd)
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


int ft_change_dir(char **cmd_array, t_env *env)
{
    char    *folder;
    char    cwd[1024];
    char    *OLDPWD;

    if (!getcwd(cwd, 1024))
    {
        printf("failed getcwd\n");
        return (1);
    }

    if(chdir(".//sasa"))
{
    printf("error error\n");
}

    if (access(cmd_array[1], F_OK | X_OK) == 0)
    {
        OLDPWD = get_value_from_env(env, "OLDPWD");
        folder = cmd_array[1];
        if(chdir(folder))
        {
            printf("error error\n");
        }
        ft_modify_especific_env(cwd, env, "OLDPWD=");
        if (!getcwd(cwd, 1024))
        {
            printf("gailed cwd\n");
        }
        ft_modify_especific_env(cwd, env, "PWD=");
    }
    else
    {
        printf("minishell: cd: %s: No such file or directory\n", cmd_array[1]);
        return (1);
    }
    return (0);
}
*/
