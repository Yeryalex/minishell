/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:17:33 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 11:06:13 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	*clean_input(char *input)
{
	if (input)
		free(input);
	return (NULL);
}

char	*read_input(char **env, t_utils *utils)
{
	char	*input;

	input = NULL;
	input = clean_input(input);
	input = readline(CYAN "minishell> " RESET);
	if (input && *input)
		add_history(input);
	else if (!input || g_signal == 130)
		utils->status = 0;
	(void)env;
	return (input);
}
