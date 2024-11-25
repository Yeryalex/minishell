/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:42:16 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/22 10:42:43 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	unsigned char	letra;

	letra = 'A';
	printf("Esta es mi letra: %c\n", letra);
	printf("Este es el resultado con toupper: %c\n", toupper(letra));
	printf("Este es el resultado con Ft_toupper: %c\n", ft_toupper(letra));
}*/
