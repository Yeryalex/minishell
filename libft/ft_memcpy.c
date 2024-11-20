/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:22:57 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/06 13:05:10 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t				i;
	const unsigned char	*csrc;
	unsigned char		*cdest;

	if (dest == src || count == 0)
		return (dest);
	cdest = (unsigned char *) dest;
	csrc = (unsigned char *) src;
	i = 0;
	while (i < count)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	origen[] = {1, 2, 3, 4, 5};
	char	destino[20] = {6, 7, 8, 9, 10, 11, 12};

	printf("El destino original antes ES: %s\n", destino);
	memcpy(destino, origen, 15);
	printf("El destino que sale con MEMCPY ES: %s\n", destino);
	printf("El valor de puntero *destino es: %s\n", destino);
	ft_memcpy(destino, origen, 15);
	printf("El destino que sale con FT_MEMCPY ES: %s\n", destino);
	return (0);
}*/
