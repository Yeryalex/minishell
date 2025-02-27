/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:34:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/11 09:36:59 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

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
