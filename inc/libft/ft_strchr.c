/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:43:59 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/08/28 17:46:53 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	i;
	int				let;

	i = 0;
	let = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == let)
			return ((char *)&s[i]);
		i++;
	}
	if (let == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
/*
int	main(void)
{
	const char		*src;
	int				c;
	const char		*resstr;
	const char		*ftstr;

	src = "hola familia que tal?tetetet";
	c = 'q';
	resstr = strchr(src, c);
	ftstr = ft_strchr(src, c);
	printf("La cadena es la siguiente: %s\n", src);
	printf("Lo que busco es: %c\n", c);
	printf("El resultado de STRCHR es: %s\n", resstr);
	printf("El resultado de FTSTRCHR es: %s\n", ftstr);
	if (resstr != NULL)
	{
		printf("Strchr dice en posicion: %ld. \n", (resstr-src));
	} else
			printf("Funcion strchr dice que NO esta: %c\n", c);
	if (ftstr != NULL)
	{
		printf("FT_strchr dice en posicion: %ld. \n", (ftstr-src));
	} else
		printf("Funcion ft_strchr dice que NO esta: %c\n", c);
}*/
