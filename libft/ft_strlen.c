/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:56:14 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/22 12:24:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
int	main(void)
{
	const char	*str;
	const char	*oristr;

	str = "";
	oristr = "";

	printf("Vamos a ver con strlen, longitud: %zu\n", strlen(oristr));
	printf("Vamos a ver con FT strlen, longitud: %zu\n", ft_strlen(str));
}*/
