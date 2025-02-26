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

static size_t	sft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	len;
	char	*newstr;

	i = 0;
	y = 0;
	len = sft_strlen(s1) + sft_strlen(s2);
	newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (NULL);
	while (s1[i])
		newstr[i++] = s1[y++];
	i = 0;
	while (s2[i])
		newstr[y++] = s2[i++];
	newstr[y] = 0;
	return (newstr);
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
