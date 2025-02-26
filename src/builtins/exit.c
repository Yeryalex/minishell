/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:46:23 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/26 12:12:39 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error_exit(char	*str, t_utils *utils, int fd)
{
	utils->exit_status = 2;
	ft_putstr_fd("exit\n", fd);
	ft_putstr_fd("minishell: exit: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(" numeric argument required\n", fd);
	if (fd == 1)
		utils->status = 0;
}

int	ft_contains_alpha(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_save_status_value(char *value, t_utils *utils, int fd)
{
	long			exit_value;
	unsigned char	exit_status;
	int				error;

	error = 0;
	exit_value = ft_atoi_long(value, &error);
	if (error)
	{
		ft_error_exit(value, utils, fd);
		return ;
	}
	exit_status = (unsigned char)(exit_value % 256);
	utils->exit_status = exit_status;
	ft_putstr_fd("exit\n", fd);
	if (fd == 1)
		utils->status = 0;
}

void	ft_handle_exit_status(char **cmd_array, t_utils *utils, int fd)
{
	if (ft_contains_alpha(cmd_array[1]))
		ft_error_exit(cmd_array[1], utils, fd);
	else if (cmd_array[2])
	{
		utils->exit_status = 1;
		ft_putstr_fd("exit\n", fd);
		ft_putstr_fd("minishell: exit: ", fd);
		ft_putstr_fd("too many arguments\n", fd);
	}
	else
		ft_save_status_value(cmd_array[1], utils, fd);
}

int	ft_exit(char **cmd_array, t_utils *utils, int fd)
{
	if (cmd_array[1])
		ft_handle_exit_status(cmd_array, utils, fd);
	else
	{
		ft_putstr_fd("exit\n", fd);
		if (fd == 1)
			utils->status = 0;
	}
	return (utils->exit_status);
}