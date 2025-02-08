/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/08 14:51:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		 g_exit_code;

static void	ft_check_args(int ac)
{
	if (!isatty(STDIN_FILENO))
	{
		perror("./minishell");
		//exit(EXIT_FAILURE);
	}
	if (ac != 1)
	{
		perror("Error ./minishell without arguments");
		//exit(EXIT_FAILURE);
	}
}

static t_utils	*ft_init_minishell(char **env, char **full_path)
{
	t_env	*environ;
	t_utils	*utils;

	utils = (t_utils *)malloc(sizeof(t_utils));
	if (!utils)
	{
		//ft_free_utils(utils);
		//perror("Error to assign memory for utils\n");
		return (NULL);
		//exit(EXIT_FAILURE);
	}

	environ = ft_init_env(env);
	if (!environ)
		return(ft_free_utils(utils), NULL);
	*full_path = ft_get_paths_from_env(environ);
	if (!*full_path)
		return(ft_clear_lstenv(environ), ft_free_utils(utils), NULL);
	init_utils(utils, environ);
	return (utils);
}

char	**ft_fill_env()
{
	char	cwd[1024];
	char	**env;
	char	*pwd;

	env = (char **)malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	if (!getcwd(cwd, 1024))
	{
		free(env);
		return (NULL);
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		free(env);
		return (NULL);
	}
	env[0] = pwd;
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = ft_strdup("PATH=/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	env[4] = NULL;
	return (env);
}

int	main(int ac, char **argv, char **env)
{
	t_utils	*utils;
	char	*full_path;
	char	**empty_env = NULL;
	int 	exit_code;

	(void)argv;
	ft_check_args(ac);
	if (!env ||!env[0])		
	{
		empty_env = ft_fill_env();
		env = empty_env;
	}
	utils = ft_init_minishell(env, &full_path);
	if (!utils)
	{
		perror("Error to asign memory for utils\n");
		//ft_free_utils(utils);
		//ft_free_array(env);
		ft_free_array(empty_env);
		exit(EXIT_FAILURE);
	}
	utils->exit_status = -1;
	prompt_loop(utils, full_path);
	exit_code = utils->exit_status;
//	free(full_path);
	ft_free_utils(utils);
//	This function is being apply for the second time
	ft_free_array(env);
	ft_free_array(empty_env);
	return (0);
}
