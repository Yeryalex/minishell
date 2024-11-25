/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:33:10 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/25 11:34:10 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
/*
int	main(void)
{
	const char	*src1;
	const char	*src2;
	size_t		x;

	src1 = "Hola12121212121212121212121";
	src2 = "Hinw";
	x = 4;
	printf(" La cadena 1 es: %s\n", src1);
	printf(" La cadena 2 es: %s\n", src2);
	printf(" Numero caracteres a comparar: %zu\n", x);
	printf(" Resultado con STRNCMP es: %d\n", strncmp(src1, src2, x));
	printf(" Resultado con FT_SRTNCMP es: %d\n", ft_strncmp(src1, src2, x));
}*/
