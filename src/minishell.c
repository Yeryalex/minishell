/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:53:25 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/11/20 13:06:23 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **argv)
{
	char	*input;
	(void)argv;
	
	if (ac != 1)
	{
		printf("Error: No parámetros al arrancar minishell.\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		// Aquí se procesará el input para manejar comandos y pipes
		free(input);
	}
	return (EXIT_SUCCESS);
}
