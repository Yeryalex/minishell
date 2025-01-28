/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:50:55 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/28 10:54:53 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_is_option(char *str)
{
	int i;

	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int	ft_handle_flag(char **cmd, int *i, int *flag)
{
	while (cmd[*i] && !ft_is_option(cmd[*i]))
	{
		*flag = 1;
		(*i)++;
	}
	return (*i);
}

int	ft_echo(char **cmd, int fd)
{
	int flag;
	int i;

	i = 1;
	ft_handle_flag(cmd, &i, &flag);
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
