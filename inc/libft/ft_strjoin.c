/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:18:09 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/29 13:51:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

/*
int	main(void)
{
	const char	*s1;
	const char	*s2;
	char		*s3;

	s1 = "Hola que tal 756464839393";
	s2 = "people";
	printf("Cadena 1 origen: %s\n", s1);
	printf("Cadena 2 destino: %s\n", s2);
	s3 = ft_strjoin(s1, s2);
	printf("Cadena 3 que resulta despues FTSTJOIN: %s\n", s3);
}*/
