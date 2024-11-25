/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 08:55:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/28 19:40:24 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, (count * size));
	return (result);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	size_t	c;
	size_t	tam;

	c = 20;
	tam = 5;
	printf("El puntero de Calloc es: %p\n", calloc(c, tam));
	printf("El interior de str de Calloc es: %s\n", calloc(c, tam));
	printf("El puntero de FTcalloc es: %p\n", ft_calloc(c, tam));
	printf("El interior str FT calloc es: %s\n", ft_calloc(c, tam));
}*/
