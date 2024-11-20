/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:28:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/07 09:49:24 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *sfind, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	if (sfind[i] == 0)
		return ((char *) src);
	while (src[i] && (i < len))
	{
		j = 0;
		while (src[i + j] == sfind[j] && (i + j) < len)
		{
			j++;
			if (sfind[j] == '\0')
				return ((char *) &src[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	*s;
	const char	*f;
	size_t		i;

	s = "pio que he sido";
	f = "que";
	i = 15;
	printf("Resultado de strnstr: %s\n", strnstr(s, f, i));
	printf("Resultado de ft strnstr: %s\n", ft_strnstr(s, f, i));
	printf("Comparando este numero: %zu\n", i);
}*/
