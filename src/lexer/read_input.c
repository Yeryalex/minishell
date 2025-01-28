/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:17:33 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:17:36 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline(CYAN "minishell> " RESET);
	if (input && *input)
		add_history(input);
	else if (!input)
		ft_putstr_fd("exit\n", 1);
	return (input);
}
