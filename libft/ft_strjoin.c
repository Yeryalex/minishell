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

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
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
