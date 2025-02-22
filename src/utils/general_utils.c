/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:07:56 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/21 11:29:47 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_valid_export(char *str)
{
	int i;
	int	counter;
	
	i = 0;
	counter = 0;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] == '_' || str[i] == '+'
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))))
			counter++;
		i++;
	}
	return (counter);
}

int ft_valid_env(char c)
{
    return (c == '_' || (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z'));
}
