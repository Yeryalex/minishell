/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:57:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/07 09:14:44 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	p = malloc((len * sizeof(char) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*mio;
	char	*str;

	if (ac == 2)
	{
		mio = ft_strdup(av[1]);
		str = strdup(av[1]);
		printf("Resultado de strdup es: %s\n", str);
		printf("Resultado de ftstrdup es %s\n", mio);
	}
	return (0);
}*/
