/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/24 11:07:11 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **argv, char **env)
{
	t_env	*environ;
	t_utils	*utils;
	int		i;
	(void)argv;
	char *full_path;
	
	i = 0;
	if (!isatty(STDIN_FILENO))
	{
		perror("./minishell");
		exit(EXIT_FAILURE);
	}
	if (ac != 1)
	{
		perror("Error ./minishel without arguments");
		return (EXIT_FAILURE);
	}
	utils = malloc(sizeof(t_utils));
	if (!utils)
	{
		perror("Error to asign memory for utils\n");
		free(utils);
		return (1);
	}

	environ = ft_init_env(env);
	full_path = ft_get_paths_from_env(environ);
	init_utils(utils, environ);		
	prompt_loop(utils, full_path);
	free(utils);
 	return (0);
}
