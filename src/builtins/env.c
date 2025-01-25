/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:04:43 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/25 11:24:38 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"


int	ft_env(t_utils *utils, int fd)
{
	t_env *temp;

	temp = utils->environ;
	while (temp)
	{
		ft_putstr_fd(temp->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(temp->value, fd);
		ft_putchar_fd('\n', fd);
		temp = temp->next;
	}
	return (0);
}
