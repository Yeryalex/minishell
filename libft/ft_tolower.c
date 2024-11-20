/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:38:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/22 10:41:39 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	unsigned char	letra;

	letra = '/';
	printf("Esta es mi letra: %c\n", letra);
	printf("Este es el resultado con tolower: %c\n", tolower(letra));
	printf("Este es el resultado con Ft_tolower: %c\n", ft_tolower(letra));
}
*/
