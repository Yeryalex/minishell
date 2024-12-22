/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/12/22 11:25:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **argv, char **env)
{
	t_env	*env_list;

	(void)argv;
	(void)env;
	
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
	env_list = ft_env_init(env);
	prompt_loop();
 	return (0);
}
