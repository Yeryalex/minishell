/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:35:49 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/25 16:13:36 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	int	res;

	i = 0;
	is_neg = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == 32 || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (is_neg)
		res *= -1;
	return (res);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	*s;

	s = "889-869";
	printf("Lo que da ATOI: %d\n", atoi(s));
	printf("Lo que da Ft Atoi: %d\n", ft_atoi(s));
	printf("Con esta cadena> %s\n", s);
}*/
