/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:17:37 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/07 09:13:40 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*malloc_error(size_t len_malloc)
{
	char	*s_malloc;

	s_malloc = malloc(sizeof(char) * len_malloc);
	if (!s_malloc)
		return (NULL);
	else
		return (s_malloc);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc_error(len + 1);
	if (!sub)
		return (NULL);
	while ((i < len) && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/*
int	main(void)
{
	const char		*str;
	unsigned int	inicio;
	size_t			len;
	char			*sub;

	str = "perico total}";
	inicio = 7;
	len = 10;
	printf("La cadena original es: %s\n", str);
	printf("Num de inicio: %d\n", inicio);
	printf("Max long: %zu\n", len);
	sub = ft_substr(str, inicio, len);
	printf("La cadena sub que resulta: %s\n", sub);
}*/
