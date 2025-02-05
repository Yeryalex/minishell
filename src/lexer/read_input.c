/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:17:33 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/31 10:57:45 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void    *clean_input(char *input)
{
    if (input)
        free(input);
    return (NULL);
}

char	*read_input(char **env)
{
	char	*input;

	input = NULL;
	input = clean_input(input);
	signal(SIGINT, ft_ctr_c);
	input = readline(CYAN "minishell> " RESET);
	if (input && *input)
		add_history(input);
	else if (!input)
		{
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        ft_free_array(env);
        exit(EXIT_SUCCESS);
    }
	return (input);
}
