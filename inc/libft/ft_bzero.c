/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:53:59 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/09 15:52:54 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (n != 0)
	{
		i = 0;
		while (i < n)
		{
			((char *)s)[i] = 0;
			i++;
		}
	}
}
/*
int	main(void)
{
	char	*str;
	size_t	n;
	size_t	i;

	str = "Hola majo";
	n = 3;
	printf("Mi cadena es: %s\n", str);
	printf("Num de ceros %zu\n", n);
	bzero(str, n);
	printf("Mi cadena BZERO es: %s\n", str);
	ft_bzero(str, n);
	// Imprimimos individualmente los caracteres después de aplicar ft_bzero
    printf("Queda con FT_bzero: %s\n", str);
	i = 0;
	while (str[i] != '\0')
	{
		printf("%c", str[i]);
        i++;
    }
    printf("\n");
    return (0);
}*/
