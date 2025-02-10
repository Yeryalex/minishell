/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:46:23 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/10 17:11:33 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	ft_error_exit(char	*str, t_utils *utils)
{
	utils->exit_status = 2;
	ft_putstr_fd("exit\n", 2);
	printf("minishell: exit: %s ", str);
	printf("numeric argument required\n");
	utils->status = 0;
}

char	*ft_init_long(long *sign, char *str)
{
	if (*str == '-' )
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

long	ft_atoi_long(char *str, int *error)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	str = ft_init_long(&sign, str);
	while (*str >= '0' && *str <= '9')
	{
		if ((result > (LONG_MAX / 10)) || (result == (LONG_MAX / 10)
				&& (*str - '0') > (LONG_MAX % 10)))
		{
			if (sign == -1 && *str == '8' && !*(str + 1))
				return (LONG_MIN);
			else if ((sign == -1 && (*str - '0') > 8) || *(str + 1))
				return (*error = 1, LONG_MIN);
			if (sign == 1)
				return (*error = 1, LONG_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
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

void	ft_save_status_value(char *value, t_utils *utils)
{
	long			exit_value;
	unsigned char	exit_status;
	int				error;

	error = 0;
	exit_value = ft_atoi_long(value, &error);
	if (error)
	{
		ft_error_exit(value, utils);
		return ;
	}
	exit_status = (unsigned char)(exit_value % 256);
	utils->exit_status = exit_status;
	ft_putstr_fd("exit\n", 2);
	utils->status = 0;
}

void	ft_handle_exit_status(char **cmd_array, t_utils *utils)
{
	if (cmd_array[2])
	{
		utils->exit_status = 1;
		ft_putstr_fd("exit\n", 2);
		printf("minishell: exit: ");
		printf("too many arguments\n");
	}
	else
	{
		if (ft_contains_alpha(cmd_array[1]))
			ft_error_exit(cmd_array[1], utils);
		else
			ft_save_status_value(cmd_array[1], utils);
	}
}

int	ft_exit(char **cmd_array, t_utils *utils)
{
	if (cmd_array[1])
		ft_handle_exit_status(cmd_array, utils);
	else
	{
		ft_putstr_fd("exit\n", 2);
		utils->status = 0;
	}
	return (0);
}
