/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:39:13 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/23 11:27:58 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cp;
	unsigned char	*s2_cp;

	s1_cp = (unsigned char *)s1;
	s2_cp = (unsigned char *)s2;
	i = 0;
	while (i < n && s1_cp[i] == s2_cp[i])
		i++;
	if (i == n)
		return (0);
	return (s1_cp[i] - s2_cp[i]);
}
/*
int	main(void)
{
	const char	*s1;
	const char	*s2;
	size_t			n;

	s1 = "pioles";
	s2 = "p1eles";
	n = 3;
	printf("Resultado con MEMCMP es: %d\n", memcmp(s1,s2,n));
	printf("Resultado con FT_MEMCMP es: %d\n", ft_memcmp(s1,s2,n));
	printf("Comparando estos bytes: %zu\n", n);
}*/
