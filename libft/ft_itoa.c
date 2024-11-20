/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:05:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/07 11:47:27 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(int n)
{
	int	cont;

	cont = 0;
	if (n >= 0 && n <= 9)
		return (1);
	else if (n < 0)
	{
		cont++;
		n *= -1;
	}
	while (n != 0)
	{
		n = n / 10;
		cont++;
	}
	return (cont);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	len;
	long	n2;

	len = count_digit(n);
	n2 = (long) n;
	num = (char *) ft_calloc((len + 1), sizeof(char));
	if (!num)
		return (NULL);
	if (n2 == 0)
		num[0] = '0';
	if (n2 < 0)
	{
		num[0] = '-';
		n2 *= -1;
	}
	len--;
	while (n2 != 0)
	{
		num[len] = (n2 % 10) + 48;
		len--;
		n2 = n2 / 10;
	}
	return (num);
}
/*
int	main(void)
{
	int		num;
	int		i;
	char	*str;

	num = -2147483648;
	printf("El número %d en cadena es: %s\n", num, ft_itoa(num));
	str = ft_itoa(num);
	i = 0;
	while (str[i] != '\0')
	{
		printf("\n Caracter %d es: %c\n", i, str[i]);
		i++;
	}
	return (0);
}*/
