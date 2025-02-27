/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/27 11:16:14 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int 	g_signal;

static void	ft_check_args(int ac)
{
	if (!isatty(STDIN_FILENO))
	{
		perror("./minishell");
		exit(EXIT_FAILURE);
	}
	if (ac != 1)
	{
		perror("Error ./minishell without arguments");
		exit(EXIT_FAILURE);
	}
}

static t_utils	*ft_init_minishell(char **env)
{
	t_env	*environ;
	t_utils	*utils;
	char	**char_env;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	environ = ft_init_env(env);
	if (!environ)
		return (free(utils), NULL);
	init_utils(utils, environ);
	char_env = ft_list_to_char(utils->environ);
	utils->env_in_char = char_env;
	return (utils);
}

char	**ft_fill_env(void)
{
	char	cwd[1024];
	char	**env;
	char	*pwd;

	env = (char **)malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	if (!getcwd(cwd, 1024))
		return (free(env), NULL);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (free(env), NULL);
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
	char	**empty_env;
	int		exit;

	(void)argv;
	ft_check_args(ac);
	if (!env || !env[0])
	{
		empty_env = ft_fill_env();
		env = empty_env;
	}
	utils = ft_init_minishell(env);
	prompt_loop(utils);
	exit = utils->exit_status;
	ft_free_utils(utils);
	return (printf("%i\n", exit), exit);
}
