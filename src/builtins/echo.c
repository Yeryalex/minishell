/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:50:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/27 12:20:03 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	flag_type1(char **cmd, int *i, int *flag)
{
	while (cmd[*i] && !ft_strncmp(cmd[*i], "-n", 3))
	{
		*flag = 1;
		*(i) = *i + 1;
	}
}

/*
int	flag_type2()
{

}
*/

int	ft_handle_flag(char **cmd, int *i, int *flag)
{
	flag_type1(cmd, i, flag);
	return (*i);
}

int	ft_echo(char **cmd, int fd)
{
	int flag = 0;
	int i;

	i = 0;
	if (!cmd[i + 1])
		return (printf(" \n"), 0);
	if (!ft_strncmp(cmd[i + 1], "-n", 3) && !cmd[i + 2])
		return (0);
	i++;
	(ft_handle_flag(cmd, &i, &flag));
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
