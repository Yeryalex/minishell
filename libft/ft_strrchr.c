/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 08:37:18 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/08/28 17:47:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	let;
	int		pos;

	pos = 0;
	let = (char) c;
	while (s[pos] != '\0')
		pos++;
	if (c == '\0')
		return ((char *) &s[pos]);
	while (pos >= 0)
	{
		if (s[pos] == let)
			return ((char *) &s[pos]);
		pos--;
	}
	return (0);
}
/*
int	main(void)
{
	const char		*src;
	int				c;
	const char		*resstr;
	const char		*ftstr;

	src = "hola familia que tal?tetetet";
	c = 'w';
	resstr = strrchr(src, c);
	ftstr = ft_strrchr(src, c);
	printf("La cadena es la siguiente: %s\n", src);
	printf("Lo que busco es: %c\n", c);
	printf("El resultado de STRRCHR es: %s\n", resstr);
	printf("El resultado de FT_STRRCHR es: %s\n", ftstr);
	if (resstr != NULL)
	{
		printf("Strrchr dice en posicion: %ld. \n", (resstr-src));
	} else
			printf("Funcion strrchr dice que NO esta: %c\n", c);
	if (ftstr != NULL)
	{
		printf("FT_strrchr dice en posicion: %ld. \n", (ftstr-src));
	} else
		printf("Ft_strrchr dice que NO esta: %c\n", c);
}*/
