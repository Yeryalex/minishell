/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/29 19:42:23 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **argv, char **env)
{
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
	prompt_loop();
 	return (0);
}
