/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:52:25 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/07 13:05:27 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = (char *) ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
		*str++ = f(i++, *s++);
	return (str - i);
}
/*
char	to_uppercase(unsigned int index, char c)
{
	return (ft_toupper(index, c));
}

int	main(void)
{
	const char	*str;
	char		*result;

	str = "Hello, World!";
	// Llamada a ft_strmapi para convertir todos los caracteres a mayúsculas
	result = ft_strmapi(str, to_uppercase);
	// Comprobamos si la llamada a ft_strmapi fue exitosa
	if (result)
	{
		// Imprimimos la cadena original y la cadena convertida
		printf("Cadena original: %s\n", str);
		printf("Cadena convertida: %s\n", result);
		// Liberamos la memoria asignada dinámicamente para la cadena convertida
		free(result);
	}
	else
	{
		// Si la llamada a ft_strmapi falla, mostramos un mensaje de error
		printf("Error: No se pudo convertir la cadena.\n");
	}
	return (0);
}*/
