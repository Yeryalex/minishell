/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:46:23 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/07 14:21:59 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_exit(char **cmd_array, t_utils *utils)
{
	(void)cmd_array;
	(void)utils;
	ft_putstr_fd("exit\n", 2);
	utils->status = 0;
	return (0);
}
