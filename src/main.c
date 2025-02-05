/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/31 08:50:23 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static t_utils	*ft_init_minishell(char **env, char **full_path)
{
	t_env	*environ;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
	{
		perror("Error to asign memory for utils\n");
		ft_free_utils(utils);
		exit(EXIT_FAILURE);
	}
	init_signals();
	environ = ft_init_env(env);
	if (!environ)
		return(free(environ), NULL);
	*full_path = ft_get_paths_from_env(environ);
	init_utils(utils, environ);
	return (utils);
}

int	main(int ac, char **argv, char **env)
{
	t_utils	*utils;
	char	*full_path;

	(void)argv;
	ft_check_args(ac);
	utils = ft_init_minishell(env, &full_path);
	prompt_loop(utils, full_path);
	free(full_path);
	ft_free_utils(utils);
	return (0);
}
