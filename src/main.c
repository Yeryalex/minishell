/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/23 11:16:03 by rbuitrag         ###   ########.fr       */
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
	//if (!env)
	//{
		environ = ft_init_env(env);
		full_path = ft_get_paths_from_env(environ);
		
	//elsels
	//	utils->check_env = 0;
	prompt_loop(environ, full_path);
 	return (0);
}
