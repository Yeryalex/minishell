/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:56:05 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/08 19:23:27 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*make_copy(unsigned char *dst, const unsigned char *src, size_t len)
{
	size_t	i;

	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dst[i] = src[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmp_dst;
	const unsigned char	*tmp_src;

	if (!src && !dst)
		return (0);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (const unsigned char *) src;
	make_copy(tmp_dst, tmp_src, len);
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char origen[] = "Hola people de Toledo";
	char destino[30] = "";

	memmove(destino, origen, 5);
	printf("\nEl resultado de origen es: %s", origen);
	printf("\nEl resultado de MEMMOVE es: %s", destino);
	ft_memmove(destino, origen, 5);
	printf("\nEl resultado de origen es: %s", origen);
	printf("\nEl resultado de FT_MEMMOVE es: %s\n", destino);
}
*/
