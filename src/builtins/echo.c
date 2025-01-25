/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:50:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/25 11:50:25 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"


int	ft_echo(char **cmd, int fd)
{
	int flag;
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (printf(" \n"), 0);
	if (!ft_strncmp(cmd[i + 1], "-n", 3) && !cmd[i + 2])
		return (0);
	i++;
	if (!ft_strncmp(cmd[i], "-n", 3))
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag != 1)
		printf("\n");
	return (0);
}
