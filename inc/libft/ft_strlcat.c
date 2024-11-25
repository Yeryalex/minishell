/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:37:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/06 12:07:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	size_t			lensrc;
	size_t			lendst;
	size_t			totalsize;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	totalsize = lensrc + lendst;
	if (!src && !dst)
		return (0);
	if (lendst >= dstsize || dstsize == 0)
		return (dstsize + lensrc);
	i = 0;
	while (src[i] && (lendst + i) < dstsize - 1)
	{
		dst[i + lendst] = src[i];
		i++;
	}
	dst[lendst + i] = 0;
	return (totalsize);
}
/*
int main(void)
{
	char	src[] = "pqrstuvwxyz";
	char	dst[] = "abcd";

	printf("Resultado de strlcat es: %lu/n", strlcat(dst, src, 20));
	printf("Resultado de FT_strlcat es: %zu/n", ft_strlcat(dst, src, 20));
}*/
