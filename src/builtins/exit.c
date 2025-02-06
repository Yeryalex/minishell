/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:46:23 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/06 20:08:05 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_exit(char **cmd_array, t_env *env)
{
	(void)cmd_array;
	(void)env;
	ft_putstr_fd("EXIT HERE\n", 2);
	return (0);
}
